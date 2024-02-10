#include <vulkan/vulkan.h>
#include <stdexcept>

#include "origami/gfx/buffer.hpp"

uint32_t find_memory_type(VkPhysicalDevice physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memory_properties;
    vkGetPhysicalDeviceMemoryProperties(physical_device, &memory_properties);

    for (uint32_t i = 0; i < memory_properties.memoryTypeCount; i++)
    {
        if ((type_filter & (1 << i)) && (memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("Buffer: failed to find suitable memory type");
}

Buffer Buffer::create(const BufferInfo &parameters)
{
    Buffer buffer;

    VkBufferCreateInfo buffer_info = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = parameters.size,
        .usage = parameters.usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VkResult result = vkCreateBuffer((VkDevice)parameters.device.device, &buffer_info, nullptr, (VkBuffer *)&buffer.id);

    if (result != VK_SUCCESS)
    {
        return buffer;
    }

    VkMemoryRequirements memory_requirements;
    vkGetBufferMemoryRequirements((VkDevice)parameters.device.device, (VkBuffer)buffer.id, &memory_requirements);

    VkMemoryAllocateInfo alloc_info{
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext = nullptr,
        .allocationSize = memory_requirements.size,
        .memoryTypeIndex = find_memory_type((VkPhysicalDevice)parameters.device.id, memory_requirements.memoryTypeBits, parameters.memory_properties),
    };

    result = vkAllocateMemory((VkDevice)parameters.device.device, &alloc_info, nullptr, (VkDeviceMemory *)&buffer.memory);

    if (result != VK_SUCCESS)
    {
        return buffer;
    }

    vkBindBufferMemory((VkDevice)parameters.device.device, (VkBuffer)buffer.id, (VkDeviceMemory)buffer.memory, 0);

    if (parameters.data)
    {
        vkMapMemory((VkDevice)parameters.device.device, (VkDeviceMemory)buffer.memory, 0, parameters.size, 0, &buffer.mapped);
        memcpy(buffer.mapped, parameters.data, parameters.size);
        vkUnmapMemory((VkDevice)parameters.device.device, (VkDeviceMemory)buffer.memory);
        buffer.mapped = nullptr;
    }

    buffer.device = parameters.device.device;

    return buffer;
}

void Buffer::destroy()
{
    vkDestroyBuffer((VkDevice)device, (VkBuffer)id, nullptr);
    vkFreeMemory((VkDevice)device, (VkDeviceMemory)memory, nullptr);
}

void Buffer::map_memory()
{
    vkMapMemory((VkDevice)device, (VkDeviceMemory)memory, 0, VK_WHOLE_SIZE, 0, &mapped);
}

void Buffer::unmap_memory()
{
    vkUnmapMemory((VkDevice)device, (VkDeviceMemory)memory);
    mapped = nullptr;
}

void Buffer::copy_to(void *data, size_t size)
{
    map_memory();
    memcpy(mapped, data, size);
    unmap_memory();
}