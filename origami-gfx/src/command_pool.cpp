#include <stdexcept>
#include <vulkan/vulkan.h>

#include "origami/gfx/command_pool.hpp"
#include "origami/gfx/command_buffer.hpp"

CommandPool CommandPool::create(const Parameters &parameters)
{
    CommandPool command_pool;

    VkCommandPoolCreateInfo create_info{
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = parameters.flags,
        .queueFamilyIndex = parameters.queue_family_index,
    };

    VkResult result = vkCreateCommandPool((VkDevice)parameters.device, &create_info, nullptr, (VkCommandPool *)&command_pool.id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::CommandPool::CommandPool(): failed to create command pool!");
    }

    command_pool.device = parameters.device;
    return command_pool;
}

void CommandPool::destroy()
{
    vkDestroyCommandPool((VkDevice)device, (VkCommandPool)id, nullptr);
}

void CommandPool::reset()
{
    vkResetCommandPool((VkDevice)device, (VkCommandPool)id, 0);
}

CommandBuffer CommandPool::allocate_command_buffer()
{
    return CommandBuffer({
        .device = device,
        .command_pool = id,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    });
}