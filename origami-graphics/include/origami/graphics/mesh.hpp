#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <origami/gfx/buffer.hpp>
#include <vector>

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
    Buffer buffer;
    enum Type
    {
        Static,
        Dynamic,
        Stream,
    } type;

    uint32_t vertices_count;

    Mesh(Type type = Static);

    Mesh(const std::vector<Vertex> &uvs, Type type = Static);

    ~Mesh();

    void set_vertices(const std::vector<Vertex> &vertices);

    inline uint32_t get_vertex_count() { return (uint32_t)vertices_count; }
};