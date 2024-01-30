#include "origami/graphics/default_pass_material.hpp"

DefaultPassMaterial::DefaultPassMaterial()
{
    // shader = Shader::from_file(
    //     "assets/shaders/default_pass",
    //     {
    //         .color_count = 1,
    //         .images = {
    //             {"u_albedo", SG_IMAGETYPE_2D},
    //             {"u_normal_ao", SG_IMAGETYPE_2D},
    //             {"u_position_roughness", SG_IMAGETYPE_2D},
    //             {"u_emissive_metallic", SG_IMAGETYPE_2D},
    //         },
    //         .depth_format = SG_PIXELFORMAT_DEPTH_STENCIL,
    //     });
}

void DefaultPassMaterial::set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model)
{
}