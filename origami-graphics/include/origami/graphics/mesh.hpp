#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <vector>
#include <sokol_gfx.h>

class GraphicEntity;

class Mesh
{
    friend class GraphicsSystem;

public:
    Mesh(std::vector<Vec3> vertices, std::vector<Vec3> normals, std::vector<Vec2> uvs, std::vector<uint32_t> indices);

    ~Mesh();

    inline size_t get_vertex_count() { return vertices_count; }

    inline size_t get_index_count() { return indices_count; }

private:
    sg_buffer vertex_buffer;
    sg_buffer index_buffer;

    size_t vertices_count;
    size_t indices_count;
};