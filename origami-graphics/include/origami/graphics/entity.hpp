#pragma once

#include <origami/core.hpp>
#include <vector>

#include "origami/graphics/mesh.hpp"
#include "origami/graphics/material.hpp"

class GraphicEntity
{
public:
    bool is_visible = true;
    Mesh *mesh = nullptr;
    Material *material = nullptr;

    GraphicEntity();

    ~GraphicEntity();

    inline void set_transform(Mat4 transform) { transform = transform; }

    Mat4 get_transform() { return transform; }

private:
    Mat4 transform;

    sg_pipeline pipeline;
};