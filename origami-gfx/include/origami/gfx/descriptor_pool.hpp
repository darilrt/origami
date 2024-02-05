#pragma once

#include <vector>
#include <cstdint>

#include "origami/gfx/type.hpp"

class DescriptorSet
{
public:
    vkid_t id = 0;
    vkid_t pool = 0;
    vkid_t layout = 0;
    vkid_t device = 0;

    struct UpdateInfo
    {
        vkid_t buffer = 0;
        uint32_t binding = 0;
        uint32_t array_element = 0;
    };

    void update(const std::vector<UpdateInfo> &updates);
};

class DescriptorPool
{
public:
    vkid_t id = 0;
    vkid_t device = 0;

    struct DescriptorPoolInfo
    {
        vkid_t device = 0;
        uint32_t descriptor_count = 0;
        uint32_t max_sets = 0;
    };

    DescriptorPool() = default;

    static DescriptorPool create(const DescriptorPoolInfo &parameters);

    void destroy();

    std::vector<DescriptorSet> allocate_descriptor_sets(const vkid_t layout, const uint32_t count);
};