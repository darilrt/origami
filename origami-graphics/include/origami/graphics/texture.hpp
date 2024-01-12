#pragma once

#include <origami/core.hpp>
#include <string>

#include "origami/graphics/sampler.hpp"
#include "origami/graphics/image.hpp"

class Texture
{
public:
    Unique<Image> image;
    Unique<Sampler> sampler;

    static Texture *load_asset(const std::string &path);
};