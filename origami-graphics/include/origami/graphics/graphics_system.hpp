#pragma once

#include <origami/core.hpp>

#include "origami/graphics/entity.hpp"
#include "origami/graphics/render_pass.hpp"

class GraphicsSystem : public Resource
{
public:
    void init(EngineState &state);

    void set_viewport(Vec4 size) { this->viewport = size; }

    void set_view(Mat4 view) { this->view = view; }

    void set_projection(Mat4 projection) { this->projection = projection; }

    void set_render_pass(Shared<RenderPass> render_pass) { this->current_render_pass = render_pass; }

    Shared<GraphicEntity> create_entity();

    Shared<RenderPass> create_render_pass(int width, int height);

private:
    std::vector<Shared<GraphicEntity>> entities;
    std::vector<Shared<RenderPass>> render_passes;
    Shared<RenderPass> current_render_pass = nullptr;
    Vec4 viewport;
    Mat4 view;
    Mat4 projection;

    void _render(Vec2 window_size);

    void _render_entity(GraphicEntity &entity);
};