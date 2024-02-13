#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <origami/gfx.hpp>
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
    enum Type
    {
        Static,
        Dynamic,
        Stream,
    } type;

    VertexArray _vao;
    Buffer _vbo;
    uint32_t _vertices_count;

    Mesh(Type type = Static);

    Mesh(const std::vector<Vertex> &uvs, Type type = Static);

    ~Mesh();

    void set_vertices(const std::vector<Vertex> &vertices);
};