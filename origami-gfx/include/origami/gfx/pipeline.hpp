#pragma once

#include "shader_module.hpp"
#include "render_pass.hpp"

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

class Pipeline
{
public:
    enum BindPoint
    {
        GRAPHICS = 0,
        COMPUTE = 1,
        RAY_TRACING = 2,
    };

    void *id = 0;
    void *layout = 0;
    void *device = 0;
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
    };

    Pipeline() = default;

    static Pipeline create(const PipelineInfo &parameters);

    void destroy();
};