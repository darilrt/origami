#include <origami/core.hpp>

#include "origami/graphics/texture.hpp"

Texture *Texture::load_asset(const std::string &path)
{
    auto *texture = new Texture();

    texture->image = Unique<Image>(Image::from_file(path));
    texture->sampler = new_unique<Sampler>(
        Sampler::Nearest,
        Sampler::Nearest,
        Sampler::Nearest,
        Sampler::Repeat,
        Sampler::Repeat);

    return texture;
}