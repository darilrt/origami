#pragma once

#include <origami/core.hpp>
#include <origami/graphics.hpp>
#include <origami/window.hpp>

class LineMaterial : public Material
{
public:
    struct
    {
        STD_UNIFORM_HEADER_VS
    } uniforms;

    LineMaterial();

    sg_range get_vs() override;

    sg_range get_fs() override;

    void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) override;
};