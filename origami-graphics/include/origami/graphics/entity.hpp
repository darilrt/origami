#pragma once

#include <origami/core.hpp>
#include <vector>

#include "origami/graphics/mesh.hpp"
#include "origami/graphics/material.hpp"

class GraphicEntity
{
public:
    bool visible = true;

    GraphicEntity();

    ~GraphicEntity();

    void set_mesh(std::shared_ptr<Mesh> mesh);

    void set_material(std::shared_ptr<Material> material);

    inline void set_transform(Mat4 transform) { transform = transform; }

    inline std::shared_ptr<Mesh> get_mesh() { return mesh; }

    inline std::shared_ptr<Material> get_material() { return material; }

    Mat4 get_transform() { return transform; }

private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    Mat4 transform;

    sg_pipeline pipeline;
};