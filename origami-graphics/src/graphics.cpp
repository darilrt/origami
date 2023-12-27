
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
}

void GraphicsSystem::init(EngineState &state)
{
    auto &window = state.get_resource<Window>();
    auto &es = state.get_resource<EventSystem>();

    es.regist<PreStart>([](EngineState &state, void *_)
                        {
        sg_desc desc = {
            .logger = slog_func,
        };
        sg_setup(&desc); });

    es.regist<Render>([&](EngineState &state, void *_)
                      {
        sg_begin_default_pass(gs_state->clear_pass, window.get_size().x, window.get_size().y);

        for (auto &entity : entities)
        {
            if (entity->visible)
            {
                std::shared_ptr<Mesh> mesh = entity->get_mesh();
                std::shared_ptr<Material> material = entity->get_material();
                auto transform = entity->get_transform();

                // material->set_uniform("u_transform", transform);
                // material->set_uniform("u_view", Mat4::identity());
                // material->set_uniform("u_projection", Mat4::identity());
                material->bind();

                // mesh->bind();
                // sg_apply_draw_state(material->get_draw_state());
                // sg_draw(0, mesh->get_vertex_count(), 1);
            }
        }

        sg_end_pass();
        sg_commit(); });

    es.regist<Stop>([](EngineState &state, void *_)
                    { sg_shutdown(); });
}

void GraphicsSystem::set_clear_color(Vec4 color)
{
    gs_state->clear_pass.colors[0].clear_value = {color.x, color.y, color.z, color.w};
}

GraphicEntity &GraphicsSystem::create_entity()
{
    entities.push_back(std::make_unique<GraphicEntity>());
    return *entities.back().get();
}