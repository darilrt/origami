#include <origami/event.hpp>
#include <origami/window.hpp>
#include <origami/gfx.hpp>
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
        [&](EngineState &state, void *_)
        { _start(state); });

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

Shared<RenderPassOld> GraphicsSystem::create_render_pass(int width, int height)
{
    auto render_pass = new_shared<RenderPassOld>(width, height);
    render_passes.push_back(render_pass);
    return render_pass;
}

void GraphicsSystem::_start(EngineState &state)
{
    auto &window = state.get_resource<Window>();

    gfx_state_ptr = new gfx::State();

    gfx::State *gfx_state = (gfx::State *)gfx_state_ptr;

    auto extensions = window.get_required_extensions();

    gfx_state->setup({
        .app_name = "Test",
        .app_version = VK_MAKE_VERSION(1, 0, 0),
        .engine_name = "Origami",
        .engine_version = VK_MAKE_VERSION(1, 0, 0),
        .api_version = VK_API_VERSION_1_0,
        .enable_validation_layers = true,
        .validation_layers = {
            "VK_LAYER_KHRONOS_validation",
        },
        .required_extensions = extensions,
        .create_surface = [&]()
        { window.create_surface_khr(gfx_state->instance, &gfx_state->surface); },
        .get_extent = [&]()
        { return VkExtent2D{
              .width = static_cast<uint32_t>(window.get_size().x),
              .height = static_cast<uint32_t>(window.get_size().y),
          }; },
    });

    // CommandPool command_pool = gfx_state->allocate_command_pool();
    // CommandBuffer cmd = command_pool.allocate_command_buffer();
    // FrameBuffer fb = gfx_state->get_current_framebuffer();

    // gfx_state->wait_for_render();

    // cmd.reset();
    // cmd.begin();

    // auto &wm = state.get_resource<Window>();

    // cmd.begin_render_pass({
    //     .render_pass = gfx_state->get_render_pass(),
    //     .framebuffer = fb,
    //     .render_area = {
    //         .x = 0,
    //         .y = 0,
    //         .width = static_cast<uint32_t>(wm.get_size().x),
    //         .height = static_cast<uint32_t>(wm.get_size().y),
    //     },
    //     .clear_values = {{0, 0, 0, 0}},
    // });

    // cmd.end_render_pass();

    // cmd.end();

    // gfx_state->submit({cmd});

    // gfx_state->draw_frame();
}

void GraphicsSystem::_render(Vec2 window_size)
{
}

void GraphicsSystem::_render_entity(GraphicEntity &entity)
{
}