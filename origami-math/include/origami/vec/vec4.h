#pragma once

#include <origami/vec/vec2.h>
#include <origami/vec/vec3.h>

class Vec4
{
public:
    union
    {
        struct
        {
            float x, y, z, w;
        };
        struct
        {
            float r, g, b, a;
        };
    };

    Vec4(float value)
    {
        data[0] = value;
        data[1] = value;
        data[2] = value;
        data[3] = value;
    }

    Vec4(float x, float y, float z, float w)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }

    Vec4()
    {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;
    }

    Vec4(const Vec2 &v, float z, float w)
    {
        data[0] = v.x;
        data[1] = v.y;
        data[2] = z;
        data[3] = w;
    }

    Vec4(const Vec2 &v, const Vec2 &w)
    {
        data[0] = v.x;
        data[1] = v.y;
        data[2] = w.x;
        data[3] = w.y;
    }

    Vec4(const Vec3 &v, float w)
    {
        data[0] = v.x;
        data[1] = v.y;
        data[2] = v.z;
        data[3] = w;
    }

    Vec4(const Vec4 &v)
    {
        data[0] = v.x;
        data[1] = v.y;
        data[2] = v.z;
        data[3] = v.w;
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

    float &operator[](int index)
    {
        return data[index];
    }

    const float &operator[](int index) const
    {
        return data[index];
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
