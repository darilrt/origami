#include "origami/graphics/mesh.hpp"
#include <cassert>

Mesh::Mesh(Type type)
{
    this->type = type;
}

Mesh::Mesh(const std::vector<Vertex> &vertices, Type type)
{
    this->type = type;
    set_vertices(vertices);
}

Mesh::~Mesh()
{
}

void Mesh::set_vertices(const std::vector<Vertex> &vertices)
{
    if (buffers.size() == 0)
        buffers.push_back(Shared<Buffer>(
            new Buffer(
                Buffer::Type::Default, static_cast<Buffer::Usage>(type))));

    vertices_count = vertices.size();

    if (vertices_count == 0)
        return;

    buffers[0]->set_data(vertices.data(), vertices.size() * sizeof(Vertex));
}
