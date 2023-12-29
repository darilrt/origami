#pragma once

#include "origami/vec/vec2.hpp"

class Bounds2D
{
public:
    Vec2 min;
    Vec2 max;

    Bounds2D() = default;

    Bounds2D(Vec2 min, Vec2 max) : min(min), max(max) {}
};