#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include "origami/graphics/image.hpp"

ImageOld::ImageOld(
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
}

ImageOld::~ImageOld()
{
}

ImageOld *ImageOld::from_file(const std::string &path)
{
    int width, height, channels;
    stbi_uc *pixels = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!pixels)
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        return nullptr;
    }

    ImageOld *image = ImageOld::from_memory(pixels, width, height);

    stbi_image_free(pixels);

    return image;
}

ImageOld *ImageOld::from_memory(const void *data, int width, int height)
{
    ImageOld *image = new ImageOld(
        width,
        height,
        1,
        RGBA8,
        Immutable,
        false,
        data);

    return image;
}

ImageOld *ImageOld::create_render_target(int width, int height)
{
    ImageOld *image = new ImageOld(
        width,
        height,
        1,
        RGBA8,
        Immutable,
        true,
        nullptr);

    return image;
}

ImageOld *ImageOld::create_depth_target(int width, int height)
{
    ImageOld *image = new ImageOld(
        width,
        height,
        1,
        Depth,
        Immutable,
        true,
        nullptr);

    return image;
}
