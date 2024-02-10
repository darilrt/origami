#pragma once

#include <optional>
#include <tuple>
#include <vector>

#include "origami/gfx/type.hpp"

class VulkanDevice
{
public:
    vkid_t id;      // VkPhysicalDevice
    vkid_t surface; // VkSurfaceKHR
    vkid_t device;  // VkDevice

    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    struct DeviceInfo
    {
        vkid_t id;
        vkid_t surface;
        std::vector<const char *> extensions;
    };

    static VulkanDevice create(DeviceInfo info);

    void destroy();

    void wait_idle();
};
