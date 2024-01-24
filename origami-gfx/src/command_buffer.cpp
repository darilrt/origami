#include <stdexcept>
#include <vulkan/vulkan.h>

#include "origami/gfx/command_buffer.hpp"

CommandBuffer::CommandBuffer(const Parameters &parameters)
{
    const VkCommandBufferAllocateInfo alloc_info{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = (VkCommandPool)parameters.command_pool,
        .level = (VkCommandBufferLevel)parameters.level,
        .commandBufferCount = 1,
    };

    VkResult result = vkAllocateCommandBuffers((VkDevice)parameters.device, &alloc_info, (VkCommandBuffer *)&id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::CommandBuffer::CommandBuffer(): failed to allocate command buffers!");
    }
}

void CommandBuffer::begin()
{
    const VkCommandBufferBeginInfo begin_info = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
    };

    vkBeginCommandBuffer((VkCommandBuffer)id, &begin_info);
}

void CommandBuffer::end()
{
    vkEndCommandBuffer((VkCommandBuffer)id);
}

void CommandBuffer::reset()
{
    vkResetCommandBuffer((VkCommandBuffer)id, 0);
}

void CommandBuffer::begin_render_pass(const RenderPassBeginInfo &info)
{
    const VkRenderPassBeginInfo begin_info = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = (VkRenderPass)info.render_pass.id,
        .framebuffer = (VkFramebuffer)info.framebuffer.id,
        .renderArea = {
            .offset = {
                .x = info.render_area.x,
                .y = info.render_area.y,
            },
            .extent = {
                .width = info.render_area.width,
                .height = info.render_area.height,
            },
        },
        .clearValueCount = (uint32_t)info.clear_values.size(),
        .pClearValues = (VkClearValue *)info.clear_values.data(),
    };

    vkCmdBeginRenderPass((VkCommandBuffer)id, &begin_info, VK_SUBPASS_CONTENTS_INLINE);
}

void CommandBuffer::end_render_pass()
{
    vkCmdEndRenderPass((VkCommandBuffer)id);
}

void CommandBuffer::set_viewport(const Viewport &viewport)
{
    vkCmdSetViewport((VkCommandBuffer)id, 0, 1, (VkViewport *)&viewport);
}

void CommandBuffer::set_scissor(const ScissorInfo &scissor)
{
    vkCmdSetScissor((VkCommandBuffer)id, 0, 1, (VkRect2D *)&scissor);
}

void CommandBuffer::draw(const DrawInfo &info)
{
    vkCmdDraw((VkCommandBuffer)id, info.vertex_count, info.instance_count, info.first_vertex, info.first_instance);
}