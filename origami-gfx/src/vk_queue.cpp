#include <vulkan/vulkan.h>

#include "origami/gfx/vk_queue.hpp"

VulkanQueue VulkanQueue::create(const CreateInfo &info)
{
    VulkanQueue queue;
    vkGetDeviceQueue((VkDevice)info.device, info.queue_family_index, info.queue_index, (VkQueue *)&queue.id);
    return queue;
}

void VulkanQueue::submit(const SubmitInfo &info)
{
    std::vector<VkSemaphore> wait_semaphores(info.wait_semaphores.size());
    for (size_t i = 0; i < info.wait_semaphores.size(); i++)
    {
        wait_semaphores[i] = (VkSemaphore)info.wait_semaphores[i].id;
    }

    std::vector<VkPipelineStageFlags> wait_stages(info.wait_stages.size());
    for (size_t i = 0; i < info.wait_stages.size(); i++)
    {
        wait_stages[i] = info.wait_stages[i];
    }

    std::vector<VkSemaphore> signal_semaphores(info.signal_semaphores.size());
    for (size_t i = 0; i < info.signal_semaphores.size(); i++)
    {
        signal_semaphores[i] = (VkSemaphore)info.signal_semaphores[i].id;
    }

    VkSubmitInfo submit_info{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = (uint32_t)wait_semaphores.size(),
        .pWaitSemaphores = wait_semaphores.data(),
        .pWaitDstStageMask = wait_stages.data(),
        .commandBufferCount = (uint32_t)info.command_buffers.size(),
        .pCommandBuffers = (VkCommandBuffer *)info.command_buffers.data(),
        .signalSemaphoreCount = (uint32_t)signal_semaphores.size(),
        .pSignalSemaphores = signal_semaphores.data(),
    };

    vkQueueSubmit((VkQueue)id, 1, &submit_info, (VkFence)info.fence.id);
}

void VulkanQueue::wait_idle()
{
    vkQueueWaitIdle((VkQueue)id);
}

void VulkanQueue::present(const PresentInfo &info)
{
    std::vector<VkSemaphore> wait_semaphores(info.wait_semaphores.size());
    for (size_t i = 0; i < info.wait_semaphores.size(); i++)
    {
        wait_semaphores[i] = (VkSemaphore)info.wait_semaphores[i].id;
    }

    std::vector<uint32_t> image_indices(info.image_indices.size());

    for (size_t i = 0; i < info.image_indices.size(); i++)
    {
        image_indices[i] = info.image_indices[i];
    }

    std::vector<VkSwapchainKHR> swap_chains(info.swap_chains.size());

    for (size_t i = 0; i < info.swap_chains.size(); i++)
    {
        swap_chains[i] = (VkSwapchainKHR)info.swap_chains[i].id;
    }

    VkPresentInfoKHR present_info{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = (uint32_t)wait_semaphores.size(),
        .pWaitSemaphores = wait_semaphores.data(),
        .swapchainCount = (uint32_t)swap_chains.size(),
        .pSwapchains = swap_chains.data(),
        .pImageIndices = image_indices.data(),
        .pResults = nullptr,
    };

    VkResult result = vkQueuePresentKHR((VkQueue)id, &present_info);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        // recreate_swap_chain();
    }
    else if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to present swap chain image");
    }
}