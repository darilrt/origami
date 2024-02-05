#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <origami/graphics/texture.hpp>

#include "origami/components/transform.hpp"

class SpriteMaterial : public Material
{
public:
};

class Sprite
{
public:
    Shared<Texture> sprite = nullptr;
    Transform2D transform = {
        .position = Vec2(0.0f),
        .rotation = 0.0f,
        .scale = Vec2(1.0f),
    };
    Shared<GraphicEntity> entity;

    void start(EngineState &state);

    void update(EngineState &state, const Update &time);

    void set_visible(bool visible);

    bool is_visible();
};