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

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> present_modes;
    };

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;

        bool is_complete()
        {
            return graphics_family.has_value() && present_family.has_value();
        }
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

        std::function<VkExtent2D()> get_extent;
        VulkanInstance instance;
        VkSurfaceKHR surface;
        VkPhysicalDevice physical_device = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphics_queue;
        VkQueue present_queue;
        VkSwapchainKHR swap_chain;
        VkFormat swap_chain_image_format;
        VkExtent2D swap_chain_extent;
        VkDebugUtilsMessengerEXT debug_messenger;
        CommandPool command_pool;
        std::vector<CommandBuffer> command_buffers;
        std::vector<VkSemaphore> image_available_semaphores;
        std::vector<VkSemaphore> render_finished_semaphores;
        std::vector<VkFence> in_flight_fences;
        uint32_t current_frame = 0;
        uint32_t image_index;
        const std::vector<const char *> device_extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        };
        bool enable_validation_layers = false;

        RenderPass render_pass;
        std::vector<Image> swap_chain_images;
        std::vector<ImageView> swap_chain_image_views;
        std::vector<FrameBuffer> swap_chain_framebuffers;

        void create_instance(const SetupInfo &info);
        void setup_debug_messenger(bool enable_validation_layers);
        void pick_physical_device();
        void create_logical_device(const SetupInfo &info);
        void create_swap_chain(const VkExtent2D &window_extent);
        void create_image_views();
        void create_render_pass();
        void create_framebuffers();
        void create_command_pool();
        void create_command_buffer();
        void create_sync_objects();
        void cleanup_swap_chain();
        void recreate_swap_chain();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
            VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
            VkDebugUtilsMessageTypeFlagsEXT message_type,
            const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
            void *user_data);

        int rate_device_suitable(VkPhysicalDevice device);
        SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device);

        QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
    };
}