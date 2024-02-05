#include <vulkan/vulkan.h>
#include <stdexcept>

#include "origami/gfx/descriptor_pool.hpp"

void DescriptorSet::update(const std::vector<UpdateInfo> &updates)
{
    std::vector<VkWriteDescriptorSet> write_sets(updates.size());
    for (size_t i = 0; i < updates.size(); i++)
    {
        VkDescriptorBufferInfo buffer_info{
            .buffer = (VkBuffer)updates[i].buffer,
            .offset = 0,
            .range = VK_WHOLE_SIZE,
        };

        write_sets[i] = {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = (VkDescriptorSet)id,
            .dstBinding = updates[i].binding,
            .dstArrayElement = updates[i].array_element,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .pBufferInfo = &buffer_info,
        };
    }

    vkUpdateDescriptorSets((VkDevice)device, (uint32_t)write_sets.size(), write_sets.data(), 0, nullptr);
}

DescriptorPool DescriptorPool::create(const DescriptorPoolInfo &parameters)
{
    DescriptorPool pool;
    pool.device = parameters.device;

    VkDescriptorPoolSize pool_sizes{
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = parameters.descriptor_count,
    };

    VkDescriptorPoolCreateInfo pool_info{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = parameters.max_sets,
        .poolSizeCount = 1,
        .pPoolSizes = &pool_sizes,
    };

    VkResult result = vkCreateDescriptorPool((VkDevice)pool.device, &pool_info, nullptr, (VkDescriptorPool *)&pool.id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create descriptor pool");
    }

    return pool;
}

void DescriptorPool::destroy()
{
    vkDestroyDescriptorPool((VkDevice)device, (VkDescriptorPool)id, nullptr);
}

std::vector<DescriptorSet> DescriptorPool::allocate_descriptor_sets(const vkid_t layout, const uint32_t count)
{
    std::vector<vkid_t> layouts(count);

    for (size_t i = 0; i < count; i++)
    {
        layouts[i] = layout;
    }

    VkDescriptorSetAllocateInfo alloc_info{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = (VkDescriptorPool)id,
        .descriptorSetCount = (uint32_t)layouts.size(),
        .pSetLayouts = (VkDescriptorSetLayout *)layouts.data(),
    };

    std::vector<VkDescriptorSet> sets(layouts.size());
    VkResult result = vkAllocateDescriptorSets((VkDevice)device, &alloc_info, (VkDescriptorSet *)sets.data());

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate descriptor sets");
    }

    std::vector<DescriptorSet> out_sets(layouts.size());
    for (size_t i = 0; i < layouts.size(); i++)
    {
        out_sets[i].id = (vkid_t)sets[i];
        out_sets[i].pool = id;
        out_sets[i].layout = layouts[i];
        out_sets[i].device = device;
    }

    return out_sets;
}