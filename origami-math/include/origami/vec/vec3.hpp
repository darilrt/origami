#pragma once

#include <cmath>

class Vec3
{
public:
    float x = 0;
    float y = 0;
    float z = 0;

    Vec3() = default;

    Vec3(float value)
    {
        x = value;
        y = value;
        z = value;
    }

    Vec3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vec3(const Vec3 &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    float dot(const Vec3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    float length() const
    {
        return sqrt(dot(*this));
    }

    float length_squared() const
    {
        return dot(*this);
    }

    Vec3 normalize() const
    {
        return *this / length();
    }

    Vec3 cross(const Vec3 &other) const
    {
        return Vec3(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
    }

    Vec3 operator+(const Vec3 &other) const
    {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3 operator-(const Vec3 &other) const
    {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator-=(const Vec3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3 operator*(const Vec3 &other) const
    {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }

    Vec3 operator*=(const Vec3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vec3 operator/(const Vec3 &other) const
    {
        return Vec3(x / other.x, y / other.y, z / other.z);
    }

    Vec3 operator/=(const Vec3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vec3 operator+(float value) const
    {
        return Vec3(x + value, y + value, z + value);
    }

    Vec3 operator+=(float value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }

    Vec3 operator-(float value) const
    {
        return Vec3(x - value, y - value, z - value);
    }

    Vec3 operator-=(float value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }

    Vec3 operator*(float value) const
    {
        return Vec3(x * value, y * value, z * value);
    }

    Vec3 operator*=(float value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vec3 operator/(float value) const
    {
        return Vec3(x / value, y / value, z / value);
    }

    Vec3 operator/=(float value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    bool operator==(const Vec3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vec3 &other) const
    {
        return !(*this == other);
    }
};