#include "origami/graphics/mesh.hpp"

Mesh::Mesh(std::vector<Vec3> vertices, std::vector<Vec3> normals, std::vector<Vec2> uvs, std::vector<uint32_t> indices)
    : vertices(vertices), normals(normals), uvs(uvs), indices(indices)
{
    bindings.vertex_buffers[0] = sg_make_buffer(sg_buffer_desc{
        .data = SG_RANGE(vertices),
        .label = "vertices",
    });
    bindings.vertex_buffers[1] = sg_make_buffer(sg_buffer_desc{
        .data = SG_RANGE(normals),
        .label = "normals",
    });
    bindings.vertex_buffers[2] = sg_make_buffer(sg_buffer_desc{
        .data = SG_RANGE(uvs),
        .label = "uvs",
    });
    bindings.index_buffer = sg_make_buffer(sg_buffer_desc{
        .type = SG_BUFFERTYPE_INDEXBUFFER,
        .data = SG_RANGE(indices),
        .label = "indices",
    });

    bindings.vertex_buffer_offsets[0] = 0;
    bindings.vertex_buffer_offsets[1] = 0;
    bindings.vertex_buffer_offsets[2] = 0;
    bindings.index_buffer_offset = 0;

    vertices_count = vertices.size();
    indices_count = indices.size();

    vertices.clear();
    normals.clear();
    uvs.clear();
    indices.clear();
}

Mesh::~Mesh()
{
    sg_destroy_buffer(bindings.vertex_buffers[0]);
    sg_destroy_buffer(bindings.vertex_buffers[1]);
    sg_destroy_buffer(bindings.vertex_buffers[2]);
    sg_destroy_buffer(bindings.index_buffer);
}