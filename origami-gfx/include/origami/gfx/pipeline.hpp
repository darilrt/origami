#pragma once

#include "origami/gfx/type.hpp"
#include "origami/gfx/shader_module.hpp"
#include "origami/gfx/render_pass.hpp"

struct BindingDescription
{
    uint32_t binding;
    uint32_t stride;
    uint32_t input_rate;
};

struct AttributeDescription
{
    uint32_t location;
    uint32_t binding;
    uint32_t format;
    uint32_t offset;
};

struct DescriptorSetLayoutBinding
{
    uint32_t binding;
    uint32_t descriptor_type;
    uint32_t descriptor_count;
    uint32_t stage_flags;
    uint32_t *immutable_samplers;
};

class Pipeline
{
public:
    enum BindPoint
    {
        GRAPHICS = 0,
        COMPUTE = 1,
        RAY_TRACING = 2,
    };

    vkid_t id = 0;
    vkid_t layout = 0;
    vkid_t device = 0;
    vkid_t descriptor_set_layout = 0;
    BindPoint bind_point;

    struct PipelineInfo
    {
        void *device = 0;
        BindPoint bind_point = GRAPHICS;
        ShaderModule vs_module;
        ShaderModule fs_module;
        RenderPass render_pass;
        std::vector<BindingDescription> binding_descriptions;
        std::vector<AttributeDescription> attribute_descriptions;
        std::vector<DescriptorSetLayoutBinding> descriptor_set_layout_bindings;
    };

    Pipeline() = default;

    static Pipeline create(const PipelineInfo &parameters);

    void destroy();
};