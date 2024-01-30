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

    struct DeviceInfo
    {
        void *id;
        void *surface;
        std::vector<const char *> extensions;
    };

    static VulkanDevice from_id(DeviceInfo info);

    void destroy();
};
