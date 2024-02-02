#pragma once

#include <cstdint>

#include "origami/gfx/vk_device.hpp"

class Buffer
{
public:
    void *id = 0;
    void *memory = 0;
    void *device = 0;

    struct BufferInfo
    {
        VulkanDevice device;
        uint32_t usage = 0;
        uint32_t memory_properties = 6;
        size_t size = 0;
        void *data = 0;
    };

    Buffer() = default;

    static Buffer create(const BufferInfo &parameters);

    void destroy();
};