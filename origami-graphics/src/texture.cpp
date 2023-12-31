#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include "origami/graphics/texture.hpp"

Image::Image(
    int width,
    int height,
    int num_mipmaps,
    Format format,
    Usage usage,
    bool render_target,
    const void *data)
{
    this->width = width;
    this->height = height;
    this->num_mipmaps = num_mipmaps;
    this->format = format;
    this->usage = usage;
    this->render_target = render_target;

    sg_image_desc desc = {
        .render_target = render_target,
        .width = width,
        .height = height,
        .num_mipmaps = num_mipmaps,
        .usage = (sg_usage)usage,
        .pixel_format = (sg_pixel_format)format,
    };

    if (data)
    {
        desc.data.subimage[0][0].ptr = data;
        desc.data.subimage[0][0].size = width * height * 4;
    }

    image = sg_make_image(&desc);
}

Image::~Image()
{
    sg_destroy_image(image);
}

Sampler::Sampler(
    Filter min_filter,
    Filter mag_filter,
    Filter mipmap_filter,
    Wrap wrap_u,
    Wrap wrap_v)
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
    Image *image = new Image(
        width,
        height,
        1,
        RGBA8,
        Immutable,
        false,
        data);

    return image;
}

Image *Image::create_render_target(int width, int height)
{
    Image *image = new Image(
        width,
        height,
        1,
        RGBA8,
        Immutable,
        true,
        nullptr);

    return image;
}

Image *Image::create_depth_target(int width, int height)
{
    Image *image = new Image(
        width,
        height,
        1,
        Depth,
        Immutable,
        true,
        nullptr);

    return image;
}
