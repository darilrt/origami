#pragma once

#include <origami/core.hpp>
#include <vector>

#include "origami/graphics/mesh.hpp"
#include "origami/graphics/material.hpp"

class GraphicEntity
{
public:
    bool is_visible = true;
    Mat4 model = Mat4::identity();
    Mesh *mesh = nullptr;
    Material *material = nullptr;
};