#pragma once

#include <origami/core.hpp>
#include <origami/gfx.hpp>
#include <origami/window.hpp>

#include "origami/graphics/entity.hpp"
#include "origami/graphics/render_pass.hpp"

class GraphicsSystem : public Resource
{
public:
    ~GraphicsSystem();

    void init(EngineState &state);

    void set_viewport(Vec4 size) { this->viewport = size; }

    void set_view(Mat4 view) { this->view = view; }

    void set_projection(Mat4 projection) { this->projection = projection; }

    void set_render_pass(Shared<RenderPass> render_pass, int index) { render_pass_stack[index] = render_pass; }

    Shared<GraphicEntity> create_entity();

    Shared<RenderPass> create_render_pass(int width, int height);

    std::vector<Shared<GraphicEntity>> entities;
    std::vector<Shared<RenderPass>> render_passes;
    std::vector<Shared<RenderPass>> render_pass_stack;
    EngineState *state;
    Vec4 viewport;
    Mat4 view = Mat4::identity();
    Mat4 projection = Mat4::identity();
    float time = 0;

    void _start(EngineState &state);

    void _update(EngineState &state, const Update &time);

    void _render(EngineState &state);

    void _render_entity(GraphicEntity &entity);
};