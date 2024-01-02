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

class GraphicsSystem::State
{
public:
    sg_pass_action clear_pass;
};

GraphicsSystem::GraphicsSystem()
{
    gs_state = new State;
    gs_state->clear_pass = {0};
}

GraphicsSystem::~GraphicsSystem()
{
    if (gs_state)
        delete gs_state;

    entities.clear();
}

void GraphicsSystem::init(EngineState &state)
{
    auto &window = state.get_resource<Window>();
    auto &es = state.get_resource<EventSystem>();

    viewport = {0, 0, window.get_size().x, window.get_size().y};

    es.regist<PreStart>([](EngineState &state, void *_)
                        {
        sg_desc desc = {
            .logger = slog_func,
        };
        sg_setup(&desc); });

    es.regist<Render>([&](EngineState &state, void *_)
                      { _render(window.get_size()); });

    es.regist<Stop>([](EngineState &state, void *_)
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
        entity->mesh = primitive::quad();
        entity->material = new DefaultPassMaterial();
        entity->model = Mat4::identity();
    }

    for (auto &rp : render_passes)
    {
        sg_begin_pass(rp->pass, &rp->action);

        set_view(rp->view);
        set_projection(rp->projection);

        for (auto &entity : entities)
        {
            _render_entity(*entity);
        }

        sg_end_pass();
    }

    sg_apply_viewport(viewport.x, viewport.y, viewport.z, viewport.w, true);
    sg_begin_default_pass(&gs_state->clear_pass, (int)window_size.x, (int)window_size.y);

    if (current_render_pass)
    {
        entity->material->set_texture(
            0,
            current_render_pass->color_attachment.get(),
            &sampler);

        _render_entity(*entity);
    }

    sg_end_pass();
    sg_commit();
}

void GraphicsSystem::_render_entity(GraphicEntity &entity)
{
    if (entity.mesh->vertices_count == 0)
        return;

    sg_bindings bindings = entity.material->bindings;
    bindings.vertex_buffers[0] = entity.mesh->vertex_buffer;

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