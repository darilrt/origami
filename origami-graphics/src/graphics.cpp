#include <origami/event.hpp>
#include <origami/window.hpp>
#include <sokol_gfx.h>
#include <sokol_log.h>

#include <iostream>

#include "origami/graphics.hpp"

class GraphicsSystem::State
{
public:
    sg_pass_action clear_pass;
};

GraphicsSystem::GraphicsSystem()
{
    gs_state = new State;
    gs_state->clear_pass = {0};
    gs_state->clear_pass.colors[0].load_action = SG_LOADACTION_CLEAR;
    gs_state->clear_pass.colors[0].clear_value = {0.1f, 0.1f, 0.1f, 1.0f};
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

void GraphicsSystem::set_clear_color(Vec4 color)
{
    gs_state->clear_pass.colors[0].clear_value = {color.x, color.y, color.z, color.w};
}

GraphicEntity &GraphicsSystem::create_entity()
{
    GraphicEntity *entity = new GraphicEntity;
    entities.push_back(entity);
    return *entity;
}

void GraphicsSystem::_render(Vec2 window_size)
{
    sg_apply_viewport(viewport.x, viewport.y, viewport.z, viewport.w, true);
    sg_begin_default_pass(&gs_state->clear_pass, (int)window_size.x, (int)window_size.y);

    for (auto &entity : entities)
    {
        if (!entity->is_visible)
            continue;

        sg_bindings bindings = entity->material->bindings;
        bindings.vertex_buffers[0] = entity->mesh->vertex_buffer;
        bindings.index_buffer = entity->mesh->index_buffer;

        sg_apply_pipeline(entity->material->shader->pipeline);
        sg_apply_bindings(&bindings);

        entity->material->set_std_uniforms(view, projection, entity->model);
        sg_range vs_params = entity->material->get_vs();
        if (vs_params.size > 0)
            sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, vs_params);

        sg_range fs_params = entity->material->get_fs();
        if (fs_params.size > 0)
            sg_apply_uniforms(SG_SHADERSTAGE_FS, 0, fs_params);

        sg_draw(0, entity->mesh->get_index_count(), 1);
    }

    sg_end_pass();
    sg_commit();
}