#pragma once

#include "origami/gfx/image.hpp"

class ImageView
{
public:
    void *id = 0;
    void *device = 0;

    struct Parameters
    {
        void *device;
        Image image;
        uint32_t view_type = 1;
        uint32_t components[4] = {0, 0, 0, 0};
        struct
        {
            uint32_t aspect_mask = 1;
            uint32_t base_mip_level = 0;
            uint32_t level_count = 1;
            uint32_t base_array_layer = 0;
            uint32_t layer_count = 1;
        } subresource_range;
    };

    ImageView() = default;

    static ImageView create(const Parameters &params);

    void destroy();
};