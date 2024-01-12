#pragma once

#include <origami/graphics/shader.hpp>
#include <origami/math.hpp>
#include <sokol_gfx.h>

#include "origami/graphics/texture.hpp"

#define STD_UNIFORM_HEADER_VS \
    Mat4 view;                \
    Mat4 projection;          \
    Mat4 model;

#define STD_UNIFORM_VS(uniforms, view, projection, model) \
    uniforms.view = view;                                 \
    uniforms.projection = projection;                     \
    uniforms.model = model;

class Material
{
    friend class GraphicEntity;

public:
    Shader *shader;
    sg_bindings bindings = {0};

    virtual sg_range get_vs() = 0;

    virtual sg_range get_fs() = 0;

    virtual void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) = 0;

    void set_texture(int slot, Shared<Texture> texture);

    void set_texture(int slot, Image *image, Sampler *sampler);
};