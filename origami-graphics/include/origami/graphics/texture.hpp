#pragma once

#include <origami/core.hpp>
#include <origami/assets.hpp>
#include <origami/gfx/image.hpp>
#include <string>

#include "origami/graphics/sampler.hpp"

class Texture
{
public:
    Unique<Image> image;
    Unique<Sampler> sampler;

    static const std::string asset_type;

    static Texture *load_asset(const std::string &path, AssetManager &assets);
};