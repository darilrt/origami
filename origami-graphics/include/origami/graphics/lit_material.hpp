#pragma once

#include <origami/graphics/material.hpp>
#include <origami/math.hpp>

class LitMaterial : public Material
{
public:
    struct
    {
        STD_UNIFORM_HEADER_VS
    } uniforms;

    LitMaterial();

    void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) override;
};