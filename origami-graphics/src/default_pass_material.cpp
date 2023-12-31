#include "origami/graphics/default_pass_material.hpp"

DefaultPassMaterial::DefaultPassMaterial()
{
    shader = Shader::from_file(
        "assets/shaders/default_pass",
        {
            .images = {
                {"u_texture", SG_IMAGETYPE_2D},
            },
            .depth_format = SG_PIXELFORMAT_DEPTH_STENCIL,
        });
}

sg_range DefaultPassMaterial::get_vs()
{
    return {nullptr, 0};
}

sg_range DefaultPassMaterial::get_fs()
{
    return {nullptr, 0};
}

void DefaultPassMaterial::set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model)
{
}