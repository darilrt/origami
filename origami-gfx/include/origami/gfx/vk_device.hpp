#pragma once

#include <optional>
#include <tuple>
#include <vector>

class VulkanDevice
{
public:
    void *id;
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

    void wait_idle();
};
