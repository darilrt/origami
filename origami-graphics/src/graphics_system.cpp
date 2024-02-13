#include <origami/event.hpp>
#include <origami/window.hpp>
#include <origami/gfx.hpp>
#include <origami/assets.hpp>
#include <iostream>
#include <string>

#include "origami/graphics/primitives.hpp"
#include "origami/graphics/material.hpp"
#include "origami/graphics/render_pass.hpp"
#include "origami/graphics/graphics_system.hpp"
#include "origami/graphics/mesh.hpp"

const int MAX_FRAMES_IN_FLIGHT = 2;

void GraphicsSystem::init(EngineState &state)
{
    gfx::init();

    this->state = &state;
    auto &es = state.get_resource<EventSystem>();

    es.regist<PreStart>(
        [&](EngineState &state, void *_)
        { _start(state); });

    es.regist<Render>(
        [&](EngineState &state, void *_)
        { _render(state); });

    es.regist<Update>(
        [&](EngineState &state, void *_)
        { _update(state, *static_cast<Update *>(_)); });

    es.regist<Stop>(
        [](EngineState &state, void *_) {});
}

Shared<GraphicEntity> GraphicsSystem::create_entity()
{
    auto entity = new_shared<GraphicEntity>();
    entities.push_back(entity);
    return entity;
}

Shared<RenderPass> GraphicsSystem::create_render_pass(int width, int height)
{
    auto render_pass = new_shared<RenderPass>(width, height);
    render_passes.push_back(render_pass);
    return render_pass;
}

GraphicsSystem::~GraphicsSystem()
{
}

void GraphicsSystem::_start(EngineState &state)
{
}

void GraphicsSystem::_update(EngineState &state, const Update &time)
{
    this->time = time.life_time;
}

void GraphicsSystem::_render(EngineState &state)
{
    static auto &window = state.get_resource<Window>();
    viewport = {0, 0, window.get_size().x, window.get_size().y};

    gfx::unbind_framebuffer();
    gfx::set_viewport(viewport.x, viewport.y, viewport.z, viewport.w);
    gfx::clear_color(0.05, 0.05, 0.06, 1.0);
    gfx::clear();
    gfx::enable_backface_culling(true);
    gfx::enable_depth_test(true);

    view = current_render_pass->view;
    projection = current_render_pass->projection;

    for (auto &_entity : entities)
    {
        _render_entity(*_entity);
    }
}

void GraphicsSystem::_render_entity(GraphicEntity &entity)
{
    entity.material->bind();

    entity.material->set_uniform("Transform", "model", &entity.model, sizeof(Mat4));
    entity.material->set_uniform("Transform", "view", &view, sizeof(Mat4));
    entity.material->set_uniform("Transform", "proj", &projection, sizeof(Mat4));
    entity.material->set_uniform("Environment", "time", &time, sizeof(float));

    entity.mesh->_vao.bind();
    gfx::draw(entity.mesh->_vertices_count);
}