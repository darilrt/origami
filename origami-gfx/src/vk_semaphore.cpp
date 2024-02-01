#include <vulkan/vulkan.h>
#include <stdexcept>

#include "origami/gfx/vk_semaphore.hpp"

VulkanSemaphore VulkanSemaphore::create(const CreateInfo &info)
{
    VulkanSemaphore semaphore;

    VkSemaphoreCreateInfo create_info{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    };

    VkResult result = vkCreateSemaphore((VkDevice)info.device, &create_info, nullptr, (VkSemaphore *)&semaphore.id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("VulkanSemaphore::create: failed to create semaphore");
    }
    return semaphore;
}

void VulkanSemaphore::destroy()
{
    vkDestroySemaphore((VkDevice)id, (VkSemaphore)id, nullptr);
}

void VulkanSemaphore::wait_for_semaphores(const std::vector<VulkanSemaphore> &semaphores, uint64_t timeout)
{
    vkWaitForFences((VkDevice)semaphores[0].id, semaphores.size(), (VkFence *)semaphores.data(), VK_TRUE, timeout);
}