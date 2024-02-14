#include <GL/glew.hpp>
#include <GL/gl.h>
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
    gfx::set_viewport(viewport.x, viewport.y, viewport.z, viewport.w);

    for (auto &render_pass : render_passes)
    {
        render_pass->begin();
        gfx::clear_color(
            render_pass->clear_color.x,
            render_pass->clear_color.y,
            render_pass->clear_color.z,
            render_pass->clear_color.w);
        gfx::clear();
        gfx::enable_backface_culling(true);
        gfx::enable_depth_test(true);

        view = render_pass->view;
        projection = render_pass->projection;

        for (auto &_entity : entities)
        {
            _render_entity(*_entity);
        }

        render_pass->end();
    }

    static auto &assets = state.get_resource<AssetManager>();
    static auto def_mat = assets.get<Material>("d06585ed-d6bc-04e9-efad-35e9f50987bb");
    static auto mesh = primitive::quad();

    gfx::unbind_framebuffer();
    gfx::clear();
    def_mat->bind();
    def_mat->set_texture("albedo", current_render_pass->color_texture);
    def_mat->set_texture("depth", current_render_pass->depth_texture);

    mesh->_vao.bind();
    gfx::draw(6);
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