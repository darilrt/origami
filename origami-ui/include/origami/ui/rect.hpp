#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <origami/graphics.hpp>

struct Rect
{
    Vec2 offset;
    Vec2 size;
};

struct ColorRect
{
    Rect rect;
    Vec4 color;
};

struct TextureRect
{
    Rect rect;
    Vec2 uv_offset;
    Vec2 uv_size;
    Shared<Texture> texture;
};