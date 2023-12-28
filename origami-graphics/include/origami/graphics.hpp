#pragma once

#include <origami/core.hpp>
#include <vector>
#include <memory>

#include "origami/graphics/mesh.hpp"
#include "origami/graphics/shader.hpp"
#include "origami/graphics/material.hpp"
#include "origami/graphics/entity.hpp"
#include "origami/graphics/primitives.hpp"

class GraphicsSystem : public Resource
{
public:
    GraphicsSystem();

    ~GraphicsSystem();

    void init(EngineState &state);

    void set_viewport(Vec4 size) { this->viewport = size; }

    void set_view(Mat4 view) { this->view = view; }

    void set_projection(Mat4 projection) { this->projection = projection; }

    void set_clear_color(Vec4 color);

    GraphicEntity &create_entity();

private:
    class State;

    State *gs_state = nullptr;
    std::vector<GraphicEntity> entities;
    Vec4 viewport;
    Mat4 view;
    Mat4 projection;

    void _render(Vec2 window_size);
};