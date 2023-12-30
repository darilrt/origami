#pragma once

#include <origami/core.hpp>
#include <origami/assets.hpp>
#include <origami/graphics/texture.hpp>

class Texture
{
public:
    std::unique_ptr<Image> image;
    std::unique_ptr<Sampler> sampler;

    static Texture *load_asset(const std::string &path);
};