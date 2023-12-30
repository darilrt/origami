#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include "origami/graphics/texture.hpp"

Sampler::Sampler(Filter min_filter, Filter mag_filter, Filter mipmap_filter, Wrap wrap_u, Wrap wrap_v)
{
    sampler = sg_make_sampler(sg_sampler_desc{
        .min_filter = (sg_filter)min_filter,
        .mag_filter = (sg_filter)mag_filter,
        .mipmap_filter = (sg_filter)mipmap_filter,
        .wrap_u = (sg_wrap)wrap_u,
        .wrap_v = (sg_wrap)wrap_v,
    });
}

Sampler::~Sampler()
{
    sg_destroy_sampler(sampler);
}

Image *Image::from_file(const std::string &path)
{
    int width, height, channels;
    stbi_uc *pixels = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!pixels)
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        return nullptr;
    }

    Image *image = Image::from_memory(pixels, width, height);

    stbi_image_free(pixels);

    return image;
}

Image *Image::from_memory(const void *data, int width, int height)
{
    sg_image_desc desc = {
        .width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
    };

    desc.data.subimage[0][0].ptr = data;
    desc.data.subimage[0][0].size = width * height * 4;

    Image *image = new Image();
    image->image = sg_make_image(&desc);

    return image;
}

Image *Image::create_render_target(int width, int height)
{
    sg_image_desc desc = {
        .render_target = true,
        .width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
    };

    Image *image = new Image();
    image->image = sg_make_image(&desc);

    return image;
}

Image *Image::create_depth_target(int width, int height)
{
    sg_image_desc desc = {
        .render_target = true,
        .width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_DEPTH,
    };

    Image *image = new Image();
    image->image = sg_make_image(&desc);

    return image;
}
