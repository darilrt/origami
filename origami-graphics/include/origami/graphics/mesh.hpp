#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <vector>

#include "origami/graphics/buffer.hpp"

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
        Static,
        Dynamic,
        Stream,
    };

    size_t vertices_count;
    std::vector<Shared<Buffer>> buffers;

    Mesh(Type type = Static);

    Mesh(const std::vector<Vertex> &uvs, Type type = Static);

    ~Mesh();

    void set_vertices(const std::vector<Vertex> &vertices);

    inline size_t get_vertex_count() { return vertices_count; }

private:
    Type type;
};