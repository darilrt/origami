#include <stdexcept>
#include <vulkan/vulkan.h>

#include "origami/gfx/image_view.hpp"

ImageView ImageView::create(const Parameters &parameters)
{
    ImageView image_view;

    VkImageViewCreateInfo description = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = reinterpret_cast<VkImage>(parameters.image.id),
        .viewType = static_cast<VkImageViewType>(parameters.view_type),
        .format = static_cast<VkFormat>(parameters.image.format),
        .components = {
            .r = static_cast<VkComponentSwizzle>(parameters.components[0]),
            .g = static_cast<VkComponentSwizzle>(parameters.components[1]),
            .b = static_cast<VkComponentSwizzle>(parameters.components[2]),
            .a = static_cast<VkComponentSwizzle>(parameters.components[3]),
        },
        .subresourceRange = {
            .aspectMask = static_cast<VkImageAspectFlags>(parameters.subresource_range.aspect_mask),
            .baseMipLevel = parameters.subresource_range.base_mip_level,
            .levelCount = parameters.subresource_range.level_count,
            .baseArrayLayer = parameters.subresource_range.base_array_layer,
            .layerCount = parameters.subresource_range.layer_count,
        },
    };

    VkResult result = vkCreateImageView(
        reinterpret_cast<VkDevice>(parameters.device),
        &description,
        nullptr,
        reinterpret_cast<VkImageView *>(&image_view.id));

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("ImageView::ImageView: failed to create image view");
    }

    image_view.device = parameters.device;

    return image_view;
}

void ImageView::destroy()
{
    vkDestroyImageView(
        reinterpret_cast<VkDevice>(device),
        reinterpret_cast<VkImageView>(id),
        nullptr);

    id = 0;
    device = 0;
}