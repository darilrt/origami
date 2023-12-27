#include "origami/graphics/entity.hpp"
#include "origami/graphics/mesh.hpp"
#include "origami/graphics/material.hpp"

GraphicEntity::GraphicEntity()
{
    pipeline.id = SG_INVALID_ID;
}

GraphicEntity::~GraphicEntity()
{
    if (pipeline.id != SG_INVALID_ID)
        sg_destroy_pipeline(pipeline);
}

void GraphicEntity::set_mesh(std::shared_ptr<Mesh> _mesh)
{
    mesh = _mesh;
}

void GraphicEntity::set_material(std::shared_ptr<Material> material)
{
    auto desc = sg_pipeline_desc{
        .shader = material->shader.shader,
    };
    desc.layout.attrs[0] = {.format = SG_VERTEXFORMAT_FLOAT3}; // position
    desc.layout.attrs[1] = {.format = SG_VERTEXFORMAT_FLOAT3}; // normal
    desc.layout.attrs[2] = {.format = SG_VERTEXFORMAT_FLOAT2}; // uv

    if (pipeline.id != SG_INVALID_ID)
        sg_destroy_pipeline(pipeline);

    pipeline = sg_make_pipeline(desc);
}
