#pragma once

#include <cstdint>

#include "origami/gfx/type.hpp"
#include "origami/gfx/vk_device.hpp"

class Buffer
{
public:
    vkid_t id = 0;
    vkid_t memory = 0;
    vkid_t device = 0;
    void *mapped = nullptr;

    struct BufferInfo
    {
        VulkanDevice device;
        uint32_t usage = 0;
        uint32_t memory_properties = 6;
        size_t size = 0;
        void *data = 0;
        bool mappable = false;
    };

    Buffer() = default;

    static Buffer create(const BufferInfo &parameters);

    void destroy();

    void map_memory();

    void unmap_memory();

    void copy_to(void *data, size_t size);
};