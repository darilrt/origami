#include <stdexcept>

#include "origami/graphics/mesh.hpp"

Mesh::Mesh(Type type) : _vao(), _vbo(BufferType::Array), _vertices_count(0), type(type)
{
    this->type = type;
}

Mesh::Mesh(const std::vector<Vertex> &vertices, Type type) : _vao(), _vbo(BufferType::Array), _vertices_count(0), type(type)
{
    set_vertices(vertices);
}

Mesh::~Mesh()
{
}

void Mesh::set_vertices(const std::vector<Vertex> &vertices)
{
    if (vertices.empty())
    {
        throw std::runtime_error("Vertices cannot be empty");
    }

    _vbo.set_data(vertices.data(), vertices.size() * sizeof(Vertex), BufferUsage::Static);

    _vao.set_attribute(_vbo, 0, 3, sizeof(Vertex), offsetof(Vertex, position));
    _vao.set_attribute(_vbo, 1, 3, sizeof(Vertex), offsetof(Vertex, normal));
    _vao.set_attribute(_vbo, 2, 2, sizeof(Vertex), offsetof(Vertex, uv));

    _vertices_count = (uint32_t)vertices.size();
}
