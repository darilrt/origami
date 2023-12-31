#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include "origami/components/transform.hpp"

class Transform
{
public:
    Transform *parent = nullptr;
    Vec3 position;
    Quat rotation = Quat::identity();
    Vec3 scale = Vec3(1.0f);

    Mat4 get_matrix() const;

    Mat4 get_inverse_matrix() const;
};

class Transform2D
{
public:
    Transform2D *parent = nullptr;
    Vec2 position;
    float rotation = 0.0f;
    Vec2 scale = Vec2(1.0f);
    float depth = 0.0f;

    Mat4 get_matrix() const;
};