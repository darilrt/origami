#pragma once

#include "shader_module.hpp"
#include "render_pass.hpp"

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

    struct Parameters
    {
        void *device = 0;
        BindPoint bind_point = GRAPHICS;
        ShaderModule vs_module;
        ShaderModule fs_module;
        RenderPass render_pass;
    };

    Pipeline() = default;

    static Pipeline create(const Parameters &parameters);

    void destroy();
};