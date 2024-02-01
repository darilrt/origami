#include <vulkan/vulkan.h>

#include "origami/gfx/image.hpp"

void Image::destroy()
{
    vkDestroyImage((VkDevice)device, (VkImage)id, nullptr);
}