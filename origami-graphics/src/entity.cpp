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