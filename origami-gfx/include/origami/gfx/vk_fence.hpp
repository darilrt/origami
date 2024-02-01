#pragma once

#include <cstdint>
#include <vector>

class VulkanFence
{
public:
    void *id;
    void *device;

    struct CreateInfo
    {
        void *device;
        uint32_t flags;
    };

    static VulkanFence create(const CreateInfo &info);

    void destroy();

    void wait();

    void reset();

    static void wait_for_fences(const std::vector<VulkanFence> &fences, uint64_t timeout);
};