#include "origami/graphics/material.hpp"

void Material::set_texture(int slot, Image *image, Sampler *sampler)
{
    bindings.fs.images[slot] = image->image;
    bindings.fs.samplers[slot] = sampler->sampler;
}