#pragma once

#include <origami/graphics/shader.hpp>
#include <origami/math.hpp>

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

    virtual void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) = 0;

    void set_texture(int slot, Shared<Texture> texture);

    void set_texture(int slot, ImageOld *image, Sampler *sampler);
};