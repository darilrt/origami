#include "origami/graphics/lit_material.hpp"

LitMaterial::LitMaterial()
{
    // shader = Shader::from_file(
    //     "assets/shaders/lit",
    //     {
    //         .uniforms_vs = {
    //             .size = sizeof(uniforms),
    //             .uniforms = {
    //                 {"view", SG_UNIFORMTYPE_MAT4},
    //                 {"projection", SG_UNIFORMTYPE_MAT4},
    //                 {"model", SG_UNIFORMTYPE_MAT4},
    //             },
    //         },
    //         .images = {
    //             {"u_albedo", SG_IMAGETYPE_2D},
    //             {"u_normal", SG_IMAGETYPE_2D},
    //             {"u_ambient_occlusion", SG_IMAGETYPE_2D},
    //             {"u_roughness", SG_IMAGETYPE_2D},
    //             {"u_emissive", SG_IMAGETYPE_2D},
    //             {"u_metallic", SG_IMAGETYPE_2D},
    //         },
    //     });
}

void LitMaterial::set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model)
{
    uniforms.view = view;
    uniforms.projection = projection;
    uniforms.model = model;
}