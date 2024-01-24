#pragma once

#include <vector>
#include <cstdint>

#include "origami/gfx/render_pass.hpp"
#include "origami/gfx/image_view.hpp"

class FrameBuffer
{
public:
    void *id = 0;
    void *device = 0;

    struct Parameters
    {
        void *device;
        RenderPass render_pass;
        uint32_t width;
        uint32_t height;
        uint32_t layers = 1;
        std::vector<ImageView> attachments;
    };

    FrameBuffer() = default;

    FrameBuffer(const Parameters &parameters);

    void destroy();
};