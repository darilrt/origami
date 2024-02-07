#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include "origami/components/transform.hpp"

class Transform
{
public:
    Shared<Transform> parent;
    Vec3 position;
    Quat rotation = Quat();
    Vec3 scale = Vec3(1.0f);

    Mat4 get_matrix() const;

    Mat4 get_inverse_matrix() const;

    // rotation methods
    void look_at(const Vec3 &target, const Vec3 &up = Vec3(0, 1, 0));

    // vector methods
    Vec3 forward();

    Vec3 right();

    Vec3 up();
};

class Transform2D
{
public:
    Unique<Transform> parent;
    Vec2 position;
    float rotation = 0.0f;
    Vec2 scale = Vec2(1.0f);
    float depth = 0.0f;

    Mat4 get_matrix() const;
};