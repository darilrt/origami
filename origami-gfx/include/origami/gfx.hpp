#pragma once

#include <iostream>
#include <vulkan/vulkan.h>
#include <origami/core.hpp>

// To enable validation layers, define ORIGAMI_ENABLE_VALIDATION_LAYERS before including origami.hpp
#ifdef ORIGAMI_ENABLE_VALIDATION_LAYERS
#define ORIGAMI_ENABLE_VALIDATION_LAYERS 1
#else
#define ORIGAMI_ENABLE_VALIDATION_LAYERS 0
#endif

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
    };

    struct State
    {
        void setup(const SetupInfo &info);

        VkInstance instance;
        VkSurfaceKHR surface;
        VkPhysicalDevice physical_device = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphics_queue;
        VkQueue present_queue;
        VkSwapchainKHR swap_chain;
        std::vector<VkImage> swap_chain_images;
        VkFormat swap_chain_image_format;
        VkExtent2D swap_chain_extent;
        std::vector<VkImageView> swap_chain_image_views;
        VkDebugUtilsMessengerEXT debug_messenger;
        std::vector<VkFramebuffer> swap_chain_framebuffers;
        VkCommandPool command_pool;
        std::vector<VkCommandBuffer> command_buffers;
        std::vector<VkSemaphore> image_available_semaphores;
        std::vector<VkSemaphore> render_finished_semaphores;
        std::vector<VkFence> in_flight_fences;
        uint32_t current_frame = 0;
        const std::vector<const char *> device_extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        };

        void create_instance(const SetupInfo &info);
        void setup_debug_messenger(const SetupInfo &info);
        void pick_physical_device();
        void create_logical_device();
        void create_surface();
        void create_swap_chain();
        void create_image_views();
        void create_command_pool();
        void create_command_buffer();
        void create_sync_objects();
        void cleanup_swap_chain();
        void recreate_swap_chain();
        void cleanup();
    };
}