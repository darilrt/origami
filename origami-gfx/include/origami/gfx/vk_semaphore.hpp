#pragma once

#include <cstdint>
#include <vector>

class VulkanSemaphore
{
public:
    void *id;

    struct CreateInfo
    {
        void *device;
    };

    static VulkanSemaphore create(const CreateInfo &info);

    void destroy();

    static void wait_for_semaphores(const std::vector<VulkanSemaphore> &semaphores, uint64_t timeout);
};