#include <vulkan/vulkan.h>
#include <stdexcept>

#include "origami/gfx/vk_fence.hpp"

VulkanFence VulkanFence::create(const CreateInfo &info)
{
    VulkanFence fence;

    VkFenceCreateInfo create_info{
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = info.flags,
    };

    VkResult result = vkCreateFence((VkDevice)info.device, &create_info, nullptr, (VkFence *)&fence.id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("VulkanFence::create: failed to create fence");
    }

    fence.device = info.device;
    return fence;
}

void VulkanFence::destroy()
{
    vkDestroyFence((VkDevice)device, (VkFence)id, nullptr);
}

void VulkanFence::wait()
{
    vkWaitForFences((VkDevice)device, 1, (VkFence *)&id, VK_TRUE, UINT64_MAX);
}

void VulkanFence::reset()
{
    vkResetFences((VkDevice)device, 1, (VkFence *)&id);
}

void VulkanFence::wait_for_fences(const std::vector<VulkanFence> &fences, uint64_t timeout)
{
    std::vector<VkFence> vk_fences(fences.size());
    for (size_t i = 0; i < fences.size(); i++)
    {
        vk_fences[i] = (VkFence)fences[i].id;
    }

    vkWaitForFences((VkDevice)fences[0].device, fences.size(), (VkFence *)vk_fences.data(), VK_TRUE, timeout);
}