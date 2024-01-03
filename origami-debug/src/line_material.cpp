#include "origami/debug/line_material.hpp"

LineMaterial::LineMaterial()
{
    shader = Shader::from_file(
        "assets/shaders/line",
        {
            .cull_mode = SG_CULLMODE_NONE,
            .primitive_type = SG_PRIMITIVETYPE_LINES,
            .uniforms_vs = {
                .size = sizeof(uniforms),
                .uniforms = {
                    {"view", SG_UNIFORMTYPE_MAT4},
                    {"projection", SG_UNIFORMTYPE_MAT4},
                    {"model", SG_UNIFORMTYPE_MAT4},
                },
            },
            .vertex_formats = {
                SG_VERTEXFORMAT_FLOAT3,
                SG_VERTEXFORMAT_FLOAT4,
            },
        });
}

sg_range LineMaterial::get_vs()
{
    return SG_RANGE(uniforms);
}

sg_range LineMaterial::get_fs()
{
    return {0, 0};
}

void LineMaterial::set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model)
{
    STD_UNIFORM_VS(uniforms, view, projection, model);
}