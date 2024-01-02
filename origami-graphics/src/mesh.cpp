#include "origami/graphics/mesh.hpp"

Mesh::Mesh(const std::vector<Vertex> &vertices, Type type)
{
    vertex_buffer = sg_make_buffer(sg_buffer_desc{
        .type = SG_BUFFERTYPE_VERTEXBUFFER,
        .usage = static_cast<sg_usage>(type),
        .data = {vertices.data(), vertices.size() * sizeof(Vertex)},
    });

    vertices_count = vertices.size();

    this->type = type;
}

Mesh::~Mesh()
{
    sg_destroy_buffer(vertex_buffer);
}

void Mesh::set_vertices(const std::vector<Vertex> &vertices)
{
    sg_update_buffer(vertex_buffer, {vertices.data(), vertices.size() * sizeof(Vertex)});
    vertices_count = vertices.size();
}