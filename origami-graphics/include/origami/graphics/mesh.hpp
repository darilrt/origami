#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <vector>
#include <sokol_gfx.h>

class GraphicEntity;

struct Vertex
{
    Vec3 position;
    Vec3 normal;
    Vec2 uv;
};

class Mesh
{
    friend class GraphicsSystem;

public:
    enum Type
    {
        Static = SG_USAGE_IMMUTABLE,
        Dynamic = SG_USAGE_DYNAMIC,
        Stream = SG_USAGE_STREAM,
    };

    Mesh(const std::vector<Vertex> &uvs, Type type = Static);

    ~Mesh();

    void set_vertices(const std::vector<Vertex> &vertices);

    inline size_t get_vertex_count() { return vertices_count; }

private:
    Type type;
    sg_buffer vertex_buffer;

    size_t vertices_count;
};