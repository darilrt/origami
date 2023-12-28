#pragma once

#include <origami/core.hpp>
#include <vector>

#include "origami/graphics/mesh.hpp"
#include "origami/graphics/material.hpp"

class GraphicEntity
{
public:
    Mat4 model;
    sg_pipeline pipeline;
    bool is_visible = true;
    Mesh *mesh = nullptr;
    Material *material = nullptr;

    GraphicEntity();

    ~GraphicEntity();
};