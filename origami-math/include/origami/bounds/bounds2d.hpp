#pragma once

#include "origami/vec/vec2.hpp"

class Bounds2D
{
public:
    Vec2 min;
    Vec2 max;

    Bounds2D() = default;

    Bounds2D(Vec2 min, Vec2 max);

    bool contains(Vec2 point);

    bool intersects(Bounds2D bounds);

    Vec2 get_center();

    Vec2 get_size();

    Vec2 get_extents();

    Vec2 get_closest_point(Vec2 point);

    static Bounds2D from_center(Vec2 center, Vec2 size);
};