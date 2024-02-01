#pragma once

#include <iostream>
#include <functional>
#include <optional>
#include <vulkan/vulkan.h>
#include <origami/core.hpp>

#include "origami/gfx/image.hpp"
#include "origami/gfx/command_pool.hpp"
#include "origami/gfx/command_buffer.hpp"
#include "origami/gfx/image_view.hpp"
#include "origami/gfx/render_pass.hpp"
#include "origami/gfx/framebuffer.hpp"
#include "origami/gfx/shader_module.hpp"
#include "origami/gfx/pipeline.hpp"
#include "origami/gfx/vk_instance.hpp"
#include "origami/gfx/vk_device.hpp"
#include "origami/gfx/swap_chain.hpp"

namespace gfx
{
    struct SetupInfo
    {
        std::string app_name;
        uint32_t app_version;
        std::string engine_name;
        uint32_t engine_version;
        uint32_t api_version;
        bool enable_validation_layers;
        std::vector<const char *> validation_layers;
        std::vector<const char *> required_extensions;
        std::function<void()> create_surface;
        VkPhysicalDeviceFeatures device_features = {};
        std::function<VkExtent2D()> get_extent;
    };

    struct State
    {
        ~State();

        void setup(const SetupInfo &info);

        void wait_for_render();

        void submit(const std::vector<CommandBuffer> &command_buffers);

        void draw_frame();

        CommandPool allocate_command_pool();

        inline RenderPass get_render_pass()
        {
            return render_pass;
        }

        inline FrameBuffer get_current_framebuffer()
        {
            return swap_chain_framebuffers[image_index];
        }

        inline CommandBuffer get_current_command_buffer()
        {
            return command_buffers[current_frame];
        }

        inline FrameBuffer get_framebuffer(size_t index)
        {
            return swap_chain_framebuffers[index];
        }

        VulkanDevice vk_device;
        std::function<VkExtent2D()> get_extent;
        VkSurfaceKHR surface;
        VulkanInstance instance;
        SwapChain swap_chain;
        CommandPool command_pool;
        std::vector<CommandBuffer> command_buffers;
        std::vector<VkSemaphore> image_available_semaphores;
        std::vector<VkSemaphore> render_finished_semaphores;
        std::vector<VkFence> in_flight_fences;
        uint32_t current_frame = 0;
        uint32_t image_index;

        RenderPass render_pass;
        std::vector<Image> swap_chain_images;
        std::vector<ImageView> swap_chain_image_views;
        std::vector<FrameBuffer> swap_chain_framebuffers;

        void create_sync_objects();
        void recreate_swap_chain();
    };
}