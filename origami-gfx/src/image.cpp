#include <vulkan/vulkan.h>
#include <iostream>
#include <stdexcept>

#include "origami/gfx/image.hpp"

uint32_t find_memory_type(VkPhysicalDevice physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties);

Image Image::create(const ImageInfo &info)
{
    Image image;

    VkImageCreateInfo image_info{
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .flags = info.flags,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = (VkFormat)info.format,
        .extent = {info.width, info.height, info.depth},
        .mipLevels = info.mip_levels,
        .arrayLayers = info.array_layers,
        .samples = (VkSampleCountFlagBits)info.samples,
        .tiling = (VkImageTiling)info.tiling,
        .usage = info.usage,
        .sharingMode = (VkSharingMode)info.sharing_mode,
        .initialLayout = (VkImageLayout)info.initial_layout,
    };

    VkResult result = vkCreateImage((VkDevice)info.device.device, &image_info, nullptr, (VkImage *)&image.id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::Image::create: failed to create image");
    }

    VkMemoryRequirements memory_requirements;
    vkGetImageMemoryRequirements((VkDevice)info.device.device, (VkImage)image.id, &memory_requirements);

    VkMemoryAllocateInfo alloc_info{
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memory_requirements.size,
        .memoryTypeIndex = find_memory_type((VkPhysicalDevice)info.device.id, memory_requirements.memoryTypeBits, info.memory_properties),
    };

    result = vkAllocateMemory((VkDevice)info.device.device, &alloc_info, nullptr, (VkDeviceMemory *)&image.memory);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::Image::create: failed to allocate image memory");
    }

    vkBindImageMemory((VkDevice)info.device.device, (VkImage)image.id, (VkDeviceMemory)image.memory, 0);

    image.device = info.device.device;
    return image;
}

void Image::destroy()
{
    vkDestroyImage((VkDevice)device, (VkImage)id, nullptr);
}