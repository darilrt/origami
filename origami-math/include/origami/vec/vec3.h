#pragma once

#include <origami/vec/vec2.h>

class Vec3
{
public:
    float data[3];

    union
    {
        struct
        {
            float x, y, z;
        };
        struct
        {
            float r, g, b;
        };
    };

    Vec3(float value)
    {
        data[0] = value;
        data[1] = value;
        data[2] = value;
    }

    Vec3(float x, float y, float z)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }

    Vec3()
    {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
    }

    Vec3(const Vec2 &v, float z)
    {
        data[0] = v.x;
        data[1] = v.y;
        data[2] = z;
    }

    Vec3(const Vec2 &v)
    {
        data[0] = v.x;
        data[1] = v.y;
        data[2] = 0;
    }

    Vec3(const Vec3 &v)
    {
        data[0] = v.x;
        data[1] = v.y;
        data[2] = v.z;
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

    float &operator[](int index)
    {
        return data[index];
    }

    const float &operator[](int index) const
    {
        return data[index];
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