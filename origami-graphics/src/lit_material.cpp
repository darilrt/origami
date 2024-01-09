#include <sokol_gfx.h>

#include "origami/graphics/lit_material.hpp"

LitMaterial::LitMaterial()
{
    shader = Shader::from_file(
        "assets/shaders/lit",
        {
            .uniforms_vs = {
                .size = sizeof(uniforms),
                .uniforms = {
                    {"view", SG_UNIFORMTYPE_MAT4},
                    {"projection", SG_UNIFORMTYPE_MAT4},
                    {"model", SG_UNIFORMTYPE_MAT4},
                },
            },
        });
}

sg_range LitMaterial::get_vs()
{
    return SG_RANGE(uniforms);
}

sg_range LitMaterial::get_fs()
{
    return {nullptr, 0};
}

void LitMaterial::set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model)
{
    uniforms.view = view;
    uniforms.projection = projection;
    uniforms.model = model;
}