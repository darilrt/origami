#pragma once

#include <optional>
#include <tuple>

class VulkanDevice
{
public:
    void *id;
    void *graphics_queue;
    void *present_queue;
    void *surface;
    void *device;

    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    struct DeviceInfo
    {
        void *id;
        void *surface;
        std::vector<const char *> extensions;
    };

    static VulkanDevice create(DeviceInfo info);

    void destroy();
};
