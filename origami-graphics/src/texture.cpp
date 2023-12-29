#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include "origami/graphics/texture.hpp"

Sampler *Sampler::from_file(const std::string &path)
{
    int width, height, channels;
    stbi_uc *pixels = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!pixels)
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        return nullptr;
    }

    sg_image_desc desc = {
        .width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
    };

    desc.data.subimage[0][0].ptr = pixels;
    desc.data.subimage[0][0].size = width * height * 4;

    Sampler *image = new Sampler();
    image->image = sg_make_image(&desc);

    stbi_image_free(pixels);

    image->sampler = sg_make_sampler(sg_sampler_desc{
        .min_filter = SG_FILTER_LINEAR,
        .mag_filter = SG_FILTER_LINEAR,
        .wrap_u = SG_WRAP_MIRRORED_REPEAT,
        .wrap_v = SG_WRAP_MIRRORED_REPEAT,
    });

    return image;
}