#pragma once

#include <cmath>

#include <origami/vec/vec2.h>
#include <origami/vec/vec3.h>

class Vec4
{
public:
    float x, y, z, w;

    Vec4(float value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
    }

    Vec4(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    Vec4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    Vec4(const Vec3 &v, float w)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = w;
    }

    Vec4(const Vec4 &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }

    float dot(const Vec4 &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    float length() const
    {
        return sqrt(dot(*this));
    }

    float length_squared() const
    {
        return dot(*this);
    }

    Vec4 normalize() const
    {
        return *this / length();
    }

    Vec4 operator+(const Vec4 &other) const
    {
        return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vec4 operator+=(const Vec4 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Vec4 operator-() const
    {
        return Vec4(-x, -y, -z, -w);
    }

    Vec4 operator-(const Vec4 &other) const
    {
        return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vec4 operator-=(const Vec4 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Vec4 operator*(const Vec4 &other) const
    {
        return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    Vec4 operator*=(const Vec4 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    Vec4 operator/(const Vec4 &other) const
    {
        return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    Vec4 operator/=(const Vec4 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    Vec4 operator+(float value) const
    {
        return Vec4(x + value, y + value, z + value, w + value);
    }

    Vec4 operator+=(float value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }

    Vec4 operator-(float value) const
    {
        return Vec4(x - value, y - value, z - value, w - value);
    }

    Vec4 operator-=(float value)
    {
        x -= value;
        y -= value;
        z -= value;
        w -= value;
        return *this;
    }

    Vec4 operator*(float value) const
    {
        return Vec4(x * value, y * value, z * value, w * value);
    }

    Vec4 operator*=(float value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    Vec4 operator/(float value) const
    {
        return Vec4(x / value, y / value, z / value, w / value);
    }

    Vec4 operator/=(float value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    bool operator==(const Vec4 &other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool operator!=(const Vec4 &other) const
    {
        return !(*this == other);
    }
};
