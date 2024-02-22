#include <iostream>
#include <origami/graphics.hpp>

#include "origami/ui.hpp"

void UI::init(EngineState &state)
{
    auto &es = state.get_resource<EventSystem>();

    es.regist<Start>(
        [&](EngineState &state, void *_)
        { _start(state); });
}

void UI::_start(EngineState &state)
{
    auto &assets = state.get_resource<AssetManager>();
    auto &window = state.get_resource<Window>();
    auto &gs = state.get_resource<GraphicsSystem>();

    Shared<RenderPass> render_pass = gs.create_render_pass(
        window.get_size().x, window.get_size().y);
    render_pass->enabled = false;
    gs.set_render_pass(render_pass, 3);

    const Vec2 offset = {0.0f, 0.0f};
    const Vec2 size = {100.0f, 100.0f};

    std::vector<Vertex> vertices = {
        {{offset.x, offset.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{offset.x + size.x, offset.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{offset.x + size.x, offset.y + size.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{offset.x, offset.y + size.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{offset.x, offset.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{offset.x + size.x, offset.y + size.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    };

    auto mesh = Shared<Mesh>(new Mesh(vertices));
    auto mat = assets.get<Material>("built-in/material/ui");
    auto tex = assets.get<Texture>("built-in/texture/gridbox");

    auto view = Mat4::ortho(0.0f, (float)window.get_size().x, (float)window.get_size().y, 0.0f, -1.0f, 1.0f);

    render_pass->begin();

    gfx::clear_color(0.1f, 0.1f, 0.1f, 0.0f);
    gfx::clear();

    mesh->_vao.bind();
    mat->bind();
    mat->set_texture("albedo", tex);
    mat->set_uniform("Camera", "proj", &view, sizeof(view));
    gfx::draw(mesh->_vertices_count);

    render_pass->end();
}