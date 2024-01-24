#pragma once

#include "shader_module.hpp"
#include "render_pass.hpp"

class Pipeline
{
public:
    void *id = 0;
    void *layout = 0;
    void *device = 0;

    struct Parameters
    {
        void *device = 0;
        ShaderModule vs_module;
        ShaderModule fs_module;
        RenderPass render_pass;
    };

    Pipeline() = default;

    Pipeline(const Parameters &parameters);

    void destroy();
};