#include "origami/graphics/material.hpp"

class DefaultPassMaterial : public Material
{
public:
    DefaultPassMaterial();

    void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) override;
};
