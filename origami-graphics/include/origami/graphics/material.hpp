#pragma once

#include <origami/graphics/shader.hpp>
#include <origami/math.hpp>
#include <sokol_gfx.h>

#define STD_UNIFORM_HEADER_VS \
    Mat4 view;                \
    Mat4 projection;          \
    Mat4 model;

class Material
{
    friend class GraphicEntity;

public:
    virtual sg_range get_vs() = 0;

    virtual sg_range get_fs() = 0;

    virtual void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) = 0;

    Shader *shader;
};