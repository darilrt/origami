#include <vulkan/vulkan.h>

#include "origami/gfx/render_pass.hpp"

RenderPass RenderPass::create(const Parameters &params)
{
    RenderPass render_pass;

    std::vector<VkAttachmentDescription> attachments;
    std::vector<VkAttachmentReference> color_attachment_refs;

    for (auto &attachment : params.attachments)
    {
        VkAttachmentDescription attachment_description{
            .format = static_cast<VkFormat>(attachment.format),
            .samples = static_cast<VkSampleCountFlagBits>(attachment.samples),
            .loadOp = static_cast<VkAttachmentLoadOp>(attachment.load_op),
            .storeOp = static_cast<VkAttachmentStoreOp>(attachment.store_op),
            .stencilLoadOp = static_cast<VkAttachmentLoadOp>(attachment.stencil_load_op),
            .stencilStoreOp = static_cast<VkAttachmentStoreOp>(attachment.stencil_store_op),
            .initialLayout = static_cast<VkImageLayout>(attachment.initial_layout),
            .finalLayout = static_cast<VkImageLayout>(attachment.final_layout),
        };
        attachments.push_back(attachment_description);

        VkAttachmentReference color_attachment_ref{
            .attachment = attachment.id,
            .layout = static_cast<VkImageLayout>(attachment.layout),
        };
        color_attachment_refs.push_back(color_attachment_ref);
    }

    VkSubpassDescription subpass{
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount = static_cast<uint32_t>(color_attachment_refs.size()),
        .pColorAttachments = color_attachment_refs.data(),
    };

    VkSubpassDependency dependency{
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass = 0,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
    };

    VkRenderPassCreateInfo render_pass_info{
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = static_cast<uint32_t>(attachments.size()),
        .pAttachments = attachments.data(),
        .subpassCount = 1,
        .pSubpasses = &subpass,
        .dependencyCount = 1,
        .pDependencies = &dependency,
    };

    VkResult result = vkCreateRenderPass((VkDevice)params.device, &render_pass_info, nullptr, (VkRenderPass *)&render_pass.id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("RenderPass::RenderPass: failed to create render pass!");
    }

    render_pass.device = params.device;
    return render_pass;
}
