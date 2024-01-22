#include <origami/event.hpp>
#include <origami/window.hpp>
#include <sokol_gfx.h>
#include <sokol_log.h>
#include <iostream>

#include "origami/graphics/primitives.hpp"
#include "origami/graphics/material.hpp"
#include "origami/graphics/render_pass.hpp"
#include "origami/graphics/graphics_system.hpp"
#include "origami/graphics/default_pass_material.hpp"

void GraphicsSystem::init(EngineState &state)
{
    auto &window = state.get_resource<Window>();
    auto &es = state.get_resource<EventSystem>();

    viewport = {0, 0, window.get_size().x, window.get_size().y};

    es.regist<PreStart>(
        [](EngineState &state, void *_)
        {
            sg_desc desc = {
                .logger = slog_func,
            };
            sg_setup(&desc);
        });

    es.regist<Render>(
        [&](EngineState &state, void *_)
        { _render(window.get_size()); });

    es.regist<Stop>(
        [](EngineState &state, void *_)
        { sg_shutdown(); });
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

void GraphicsSystem::_render(Vec2 window_size)
{
    static GraphicEntity *entity = nullptr;
    static Sampler sampler = Sampler(
        Sampler::Nearest,
        Sampler::Nearest,
        Sampler::Nearest,
        Sampler::Repeat,
        Sampler::Repeat);

    if (!entity)
    {
        entity = new GraphicEntity();
        entity->mesh = Shared<Mesh>(primitive::quad());
        entity->material = new_shared<DefaultPassMaterial>();
        entity->model = Mat4::identity();
    }
}

void GraphicsSystem::_render_entity(GraphicEntity &entity)
{
    if (!entity.mesh || !entity.material)
        return;

    if (!entity.mesh->get_vertex_count())
        return;

    sg_bindings bindings = entity.material->bindings;

    int i = 0;
    for (auto &buffer : entity.mesh->buffers)
    {
        bindings.vertex_buffers[i++] = buffer->buffer;
    }

    sg_apply_pipeline(entity.material->shader->pipeline);
    sg_apply_bindings(&bindings);

    entity.material->set_std_uniforms(view, projection, entity.model);
    sg_range vs_params = entity.material->get_vs();
    if (vs_params.size > 0)
        sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, vs_params);

    sg_range fs_params = entity.material->get_fs();
    if (fs_params.size > 0)
        sg_apply_uniforms(SG_SHADERSTAGE_FS, 0, fs_params);

    sg_draw(0, entity.mesh->get_vertex_count(), 1);
}