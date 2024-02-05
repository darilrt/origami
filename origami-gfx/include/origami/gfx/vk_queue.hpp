#pragma once

#include <cstdint>
#include <vector>

#include "origami/gfx/type.hpp"
#include "origami/gfx/vk_semaphore.hpp"
#include "origami/gfx/vk_fence.hpp"
#include "origami/gfx/command_buffer.hpp"
#include "origami/gfx/swap_chain.hpp"

class VulkanQueue
{
public:
    vkid_t id;

    struct CreateInfo
    {
        vkid_t device;
        uint32_t queue_family_index;
        uint32_t queue_index;
    };

    static VulkanQueue create(const CreateInfo &info);

    void destroy();

    struct SubmitInfo
    {
        std::vector<vkid_t> command_buffers;
        std::vector<VulkanSemaphore> wait_semaphores;
        std::vector<uint32_t> wait_stages;
        std::vector<VulkanSemaphore> signal_semaphores;
        VulkanFence fence;
    };

    void submit(const SubmitInfo &info);

    void wait_idle();

    struct PresentInfo
    {
        std::vector<VulkanSemaphore> wait_semaphores;
        std::vector<uint32_t> image_indices;
        std::vector<SwapChain> swap_chains;
    };

    void present(const PresentInfo &info);
};