#pragma once

#include <origami.hpp>

class SimpleMaterial : public Material
{
public:
    struct
    {
        STD_UNIFORM_HEADER_VS
    } uniforms;

    SimpleMaterial()
    {
        shader = Shader::from_file(
            "assets/shaders/default",
            Shader::Descriptor{
                .uniforms_vs = {
                    .size = sizeof(uniforms),
                    .uniforms = {
                        {"view", SG_UNIFORMTYPE_MAT4},
                        {"projection", SG_UNIFORMTYPE_MAT4},
                        {"model", SG_UNIFORMTYPE_MAT4},
                    },
                },
                .images = {
                    {"tex", SG_IMAGETYPE_2D},
                },
            });
    }

    sg_range get_vs() override
    {
        return {&uniforms, sizeof(uniforms)};
    }

    sg_range get_fs() override
    {
        return {nullptr, 0};
    }

    void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) override
    {
        uniforms.view = view;
        uniforms.projection = projection;
        uniforms.model = model;
    }
};
