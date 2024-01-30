#pragma once

#include <string>
#include <vector>

#include "origami/gfx/vk_device.hpp"

#define VULKAN_DEBUG

class VulkanInstance
{
public:
    void *id;

#ifdef VULKAN_DEBUG
    void *debug_messenger;
#endif

    struct AppInfo
    {
        std::string app_name;
        uint32_t app_version;
        std::string engine_name;
        uint32_t engine_version;
        uint32_t api_version;
    };

    struct InstanceInfo
    {
        AppInfo app_info;
        std::vector<const char *> validation_layers;
        std::vector<const char *> required_extensions;
    };

    static VulkanInstance create(const InstanceInfo &info);

    void destroy();

    VulkanDevice create_device(void *surface);
};