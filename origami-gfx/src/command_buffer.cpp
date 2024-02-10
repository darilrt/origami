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

    command_pool = parameters.command_pool;
    device = parameters.device;
}

void CommandBuffer::begin(uint32_t flags)
{
    const VkCommandBufferBeginInfo begin_info = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = flags,
    };

    vkBeginCommandBuffer((VkCommandBuffer)id, &begin_info);
}

void CommandBuffer::end()
{
    vkEndCommandBuffer((VkCommandBuffer)id);
}

void CommandBuffer::destroy()
{
    vkFreeCommandBuffers((VkDevice)device, (VkCommandPool)command_pool, 1, (VkCommandBuffer *)&id);
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

void CommandBuffer::bind_pipeline(const Pipeline &pipeline)
{
    vkCmdBindPipeline((VkCommandBuffer)id, (VkPipelineBindPoint)pipeline.bind_point, (VkPipeline)pipeline.id);
}

void CommandBuffer::bind_descriptor_sets(const DescriptorSetInfo &info)
{
    vkCmdBindDescriptorSets(
        (VkCommandBuffer)id,
        (VkPipelineBindPoint)info.pipeline_bind_point,
        (VkPipelineLayout)info.pipeline_layout,
        info.first_set,
        1,
        (VkDescriptorSet *)info.descriptor_sets.data(),
        0,
        nullptr);
}

void CommandBuffer::draw(const DrawInfo &info)
{
    vkCmdDraw((VkCommandBuffer)id, info.vertex_count, info.instance_count, info.first_vertex, info.first_instance);
}

void CommandBuffer::bind_vertex_buffers(const std::vector<void *> &buffers, const std::vector<uint64_t> &offsets)
{
    vkCmdBindVertexBuffers((VkCommandBuffer)id, 0, (uint32_t)buffers.size(), (VkBuffer *)buffers.data(), (VkDeviceSize *)offsets.data());
}

void CommandBuffer::copy_buffer(vkid_t src, vkid_t dst, uint64_t size)
{
    VkBufferCopy copy_region = {
        .srcOffset = 0,
        .dstOffset = 0,
        .size = size,
    };

    vkCmdCopyBuffer((VkCommandBuffer)id, (VkBuffer)src, (VkBuffer)dst, 1, &copy_region);
}

void CommandBuffer::copy_buffer_to_image(vkid_t src, vkid_t dst, uint32_t width, uint32_t height, uint32_t depth)
{
    VkBufferImageCopy region = {
        .bufferOffset = 0,
        .bufferRowLength = 0,
        .bufferImageHeight = 0,
        .imageSubresource = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .mipLevel = 0,
            .baseArrayLayer = 0,
            .layerCount = 1,
        },
        .imageOffset = {0, 0, 0},
        .imageExtent = {width, height, depth},
    };

    vkCmdCopyBufferToImage((VkCommandBuffer)id, (VkBuffer)src, (VkImage)dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
}