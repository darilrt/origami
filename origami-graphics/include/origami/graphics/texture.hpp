#pragma once

#include <origami/core.hpp>
#include <origami/gfx/image.hpp>
#include <string>

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

#include "origami/graphics/sampler.hpp"
#include "origami/graphics/image.hpp"

class Texture
{
public:
    Unique<Image> image;
    Unique<Sampler> sampler;

    static Texture *load_asset(const std::string &path);
};