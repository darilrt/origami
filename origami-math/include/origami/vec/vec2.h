#pragma once

#include <cmath>

#include <origami/vec/vec3.h>
#include <origami/vec/vec4.h>

class Vec2
{
public:
    float x, y;

    Vec2(float value)
    {
        x = value;
        y = value;
    }

    Vec2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    Vec2(const Vec2 &other)
    {
        x = other.x;
        y = other.y;
    }

    Vec2(const Vec3 &other)
    {
        x = other.x;
        y = other.y;
    }

    Vec2(const Vec4 &other)
    {
        x = other.x;
        y = other.y;
    }

    Vec2()
    {
        x = 0;
        y = 0;
    }

    float dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    float length() const
    {
        return sqrt(dot(*this));
    }

    float length_squared() const
    {
        return dot(*this);
    }

    Vec2 normalize() const
    {
        return *this / length();
    }

    Vec2 operator+(const Vec2 &other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator+=(const Vec2 &other)
    {
        *this = *this + other;
        return *this;
    }

    Vec2 operator-(const Vec2 &other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator-=(const Vec2 &other)
    {
        *this = *this - other;
        return *this;
    }

    Vec2 operator*(const Vec2 &other) const
    {
        return Vec2(x * other.x, y * other.y);
    }

    Vec2 operator*=(const Vec2 &other)
    {
        *this = *this * other;
        return *this;
    }

    Vec2 operator/(const Vec2 &other) const
    {
        return Vec2(x / other.x, y / other.y);
    }

    Vec2 operator/=(const Vec2 &other)
    {
        *this = *this / other;
        return *this;
    }

    Vec2 operator+(float value) const
    {
        return Vec2(x + value, y + value);
    }

    Vec2 operator+=(float value)
    {
        *this = *this + value;
        return *this;
    }

    Vec2 operator-(float value) const
    {
        return Vec2(x - value, y - value);
    }

    Vec2 operator-=(float value)
    {
        *this = *this - value;
        return *this;
    }

    Vec2 operator*(float value) const
    {
        return Vec2(x * value, y * value);
    }

    Vec2 operator*=(float value)
    {
        *this = *this * value;
        return *this;
    }

    Vec2 operator/(float value) const
    {
        return Vec2(x / value, y / value);
    }

    Vec2 operator/=(float value)
    {
        *this = *this / value;
        return *this;
    }

    Vec2 operator-() const
    {
        return Vec2(-x, -y);
    }

    bool operator==(const Vec2 &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2 &other) const
    {
        return x != other.x || y != other.y;
    }
};