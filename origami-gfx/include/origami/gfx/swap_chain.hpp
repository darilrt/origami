#pragma once

#include <cstdint>
#include <vector>

#include "origami/gfx/vk_device.hpp"
#include "origami/gfx/vk_semaphore.hpp"
#include "origami/gfx/image.hpp"

class SwapChain
{
public:
    void *id;
    void *device;
    std::vector<Image> images;

    struct SwapChainInfo
    {
        VulkanDevice device;
        struct
        {
            uint32_t width;
            uint32_t height;
        } extent;
    };

    static SwapChain create(const SwapChainInfo &info);

    void destroy();

    uint32_t acquire_next_image(VulkanSemaphore semaphore);
};