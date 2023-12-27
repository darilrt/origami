#include "origami/mesh.hpp"

StaticMesh::StaticMesh(std::vector<Vec3> vertices, std::vector<Vec3> normals, std::vector<Vec2> uvs, std::vector<uint32_t> indices)
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
}