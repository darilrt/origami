#pragma once

#include <cstdint>

#include "origami/gfx/type.hpp"
#include "origami/gfx/vk_device.hpp"

class Image
{
public:
    vkid_t id = 0;
    vkid_t memory = 0;
    vkid_t device = 0;

    enum Format
    {
        BGRA = 50,
        RGBA = 43,
    } format;

    struct ImageInfo
    {
        VulkanDevice device;
        uint32_t width;
        uint32_t height;
        uint32_t depth = 1;
        uint32_t mip_levels = 1;
        uint32_t array_layers = 1;
        uint32_t samples = 1;
        uint32_t format = 43;
        uint32_t tiling = 0;
        uint32_t initial_layout = 0;
        uint32_t usage = 0;
        uint32_t sharing_mode = 0;
        uint32_t memory_properties = 1;
        uint32_t flags = 0;
    };

    Image() = default;

    static Image create(const ImageInfo &params);

    void destroy();
};
