#pragma once

#include <cstdint>

class Image
{
public:
    void *id = 0;
    void *device = 0;

    struct Parameters
    {
        void *device;
        uint32_t width;
        uint32_t height;
        uint32_t depth = 1;
        uint32_t mip_levels = 1;
        uint32_t array_layers = 1;
        uint32_t samples = 1;
        uint32_t format = 37;
        uint32_t tiling = 0;
        uint32_t usage = 0;
        uint32_t memory_properties = 1;
        uint32_t initial_layout = 0;
    };

    Image() = default;
};
