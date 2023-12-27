#pragma once

#include <origami/core.hpp>
#include <vector>
#include <memory>

#include "origami/graphics/mesh.hpp"
#include "origami/graphics/shader.hpp"
#include "origami/graphics/material.hpp"
#include "origami/graphics/entity.hpp"

class GraphicsSystem : public Resource
{
public:
    GraphicsSystem();

    ~GraphicsSystem();

    void init(EngineState &state);

    void set_clear_color(Vec4 color);

    GraphicEntity &create_entity();

private:
    class State;

    State *gs_state = nullptr;

    std::vector<std::unique_ptr<GraphicEntity>> entities;
};