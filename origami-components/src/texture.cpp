#include <origami/graphics/texture.hpp>

#include "origami/components/texture.hpp"

Texture *Texture::load_asset(const std::string &path)
{
    auto *texture = new Texture();

    texture->image = std::unique_ptr<Image>(Image::from_file(path));
    texture->sampler = std::make_unique<Sampler>(
        Sampler::Nearest,
        Sampler::Nearest,
        Sampler::Nearest,
        Sampler::Repeat,
        Sampler::Repeat);

    return texture;
}