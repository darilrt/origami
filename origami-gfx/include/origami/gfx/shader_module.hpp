#pragma once

#include "origami/gfx/gfx_defs.hpp"

enum class ShaderType
{
    Vertex = 0x8B31,
    Fragment = 0x8B30,
    Geometry = 0x8DD9,
    TessControl = 0x8E88,
    TessEvaluation = 0x8E87,
    Compute = 0x91B9
};

class ShaderModule
{
public:
    glid_t _id;

    ShaderModule(ShaderType type);
    ~ShaderModule();

    void set_source(const char *source);
    void compile();
};