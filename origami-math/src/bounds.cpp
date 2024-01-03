#include "origami/math/math.hpp"
#include "origami/bounds/bounds2d.hpp"

Bounds2D::Bounds2D(Vec2 min, Vec2 max)
{
    this->min = min;
    this->max = max;
}

bool Bounds2D::contains(Vec2 point)
{
    return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y;
}

bool Bounds2D::intersects(Bounds2D bounds)
{
    return min.x <= bounds.max.x && max.x >= bounds.min.x && min.y <= bounds.max.y && max.y >= bounds.min.y;
}

Vec2 Bounds2D::get_center()
{
    return (min + max) / 2.0f;
}

Vec2 Bounds2D::get_size()
{
    return max - min;
}

Vec2 Bounds2D::get_extents()
{
    return get_size() / 2.0f;
}

Vec2 Bounds2D::get_closest_point(Vec2 point)
{
    return Vec2(
        math::clamp(point.x, min.x, max.x),
        math::clamp(point.y, min.y, max.y));
}

Bounds2D Bounds2D::from_center(Vec2 center, Vec2 size)
{
    return Bounds2D(center - size / 2.0f, center + size / 2.0f);
}