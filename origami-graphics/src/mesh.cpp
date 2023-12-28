#include "origami/graphics/mesh.hpp"

Mesh::Mesh(std::vector<Vec3> vertices, std::vector<Vec3> normals, std::vector<Vec2> uvs, std::vector<uint32_t> indices)
{
    vertex_buffer = sg_make_buffer(sg_buffer_desc{
        .data = {vertices.data(), vertices.size() * sizeof(Vec3)},
    });
    index_buffer = sg_make_buffer(sg_buffer_desc{
        .type = SG_BUFFERTYPE_INDEXBUFFER,
        .data = {indices.data(), indices.size() * sizeof(uint32_t)},
    });

    vertices_count = vertices.size();
    indices_count = indices.size();
}

Mesh::~Mesh()
{
    sg_destroy_buffer(vertex_buffer);
    sg_destroy_buffer(index_buffer);
}