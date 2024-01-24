#include "origami/graphics/material.hpp"

void Material::set_texture(int slot, Shared<Texture> texture)
{
    bindings.fs.images[slot] = texture->image->image;
    bindings.fs.samplers[slot] = texture->sampler->sampler;
}

void Material::set_texture(int slot, ImageOld *image, Sampler *sampler)
{
    bindings.fs.images[slot] = image->image;
    bindings.fs.samplers[slot] = sampler->sampler;
}