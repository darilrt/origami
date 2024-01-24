#include <stdexcept>
#include <vulkan/vulkan.h>

#include "origami/gfx/framebuffer.hpp"

FrameBuffer::FrameBuffer(const Parameters &parameters)
{
    std::vector<VkImageView> attachments(parameters.attachments.size());

    for (size_t i = 0; i < parameters.attachments.size(); i++)
    {
        attachments[i] = static_cast<VkImageView>(parameters.attachments[i].id);
    }

    VkFramebufferCreateInfo description = {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = static_cast<VkRenderPass>(parameters.render_pass.id),
        .attachmentCount = static_cast<uint32_t>(attachments.size()),
        .pAttachments = attachments.data(),
        .width = parameters.width,
        .height = parameters.height,
        .layers = parameters.layers,
    };

    VkResult result = vkCreateFramebuffer(
        static_cast<VkDevice>(parameters.device),
        &description,
        nullptr,
        reinterpret_cast<VkFramebuffer *>(&id));

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("FrameBuffer::FrameBuffer: failed to create framebuffer");
    }

    device = parameters.device;
}

void FrameBuffer::destroy()
{
    vkDestroyFramebuffer(
        static_cast<VkDevice>(device),
        static_cast<VkFramebuffer>(id),
        nullptr);

    id = 0;
    device = 0;
}