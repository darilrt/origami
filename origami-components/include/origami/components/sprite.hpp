#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include "origami/components/transform.hpp"

class SpriteMaterial : public Material
{
public:
    struct
    {
        STD_UNIFORM_HEADER_VS
    } uniforms;

    SpriteMaterial();

    sg_range get_vs() override;

    sg_range get_fs() override;

    void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) override;
};

class Sprite
{
public:
    std::shared_ptr<Sampler> sampler;
    Transform2D transform;
    GraphicEntity *entity;

    void start(EngineState &state);

    void update(EngineState &state, const Update &time);

    void set_visible(bool visible);

    bool is_visible();
};