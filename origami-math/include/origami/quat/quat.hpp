#pragma once

#include <cmath>

#include "origami/vec/vec3.hpp"
#include "origami/vec/vec4.hpp"

class Mat4;

class Quat
{
public:
    float data[4];

    union
    {
        struct
        {
            float i, j, k, r;
        };
    };

    Quat(float value)
    {
        data[0] = value;
        data[1] = value;
        data[2] = value;
        data[3] = value;
    }

    Quat(float i, float j, float k, float r)
    {
        data[0] = i;
        data[1] = j;
        data[2] = k;
        data[3] = r;
    }

    Quat()
    {
        data[0] = 0.0;
        data[1] = 0.0;
        data[2] = 0.0;
        data[3] = 1.0;
    }

    Quat normalize()
    {
        float length = sqrt(i * i + j * j + k * k + r * r);
        return Quat(i / length, j / length, k / length, r / length);
    }

    Quat conjugate()
    {
        return Quat(-i, -j, -k, r);
    }

    Quat inverse()
    {
        return conjugate() / (i * i + j * j + k * k + r * r);
    }

    float dot(const Quat &b)
    {
        return i * b.i + j * b.j + k * b.k + r * b.r;
    }

    static Quat lerp(Quat &a, Quat &b, float t)
    {
        return (a * (1.0f - t) + b * t).normalize();
    }

    static Quat identity()
    {
        return Quat();
    }

    static Quat from_axis_angle(const Vec3 &axis, float angle)
    {
        float half_angle = angle * 0.5;
        float sin_half_angle = sin(half_angle);
        return Quat(axis.x * sin_half_angle, axis.y * sin_half_angle, axis.z * sin_half_angle, cos(half_angle));
    }

    static Quat from_euler(const Vec3 &euler)
    {
        float half_x = euler.x * 0.5;
        float half_y = euler.y * 0.5;
        float half_z = euler.z * 0.5;

        float sin_half_x = sin(half_x);
        float sin_half_y = sin(half_y);
        float sin_half_z = sin(half_z);

        float cos_half_x = cos(half_x);
        float cos_half_y = cos(half_y);
        float cos_half_z = cos(half_z);

        return Quat(
            cos_half_y * sin_half_x * cos_half_z + sin_half_y * cos_half_x * sin_half_z,
            sin_half_y * cos_half_x * cos_half_z - cos_half_y * sin_half_x * sin_half_z,
            cos_half_y * cos_half_x * sin_half_z - sin_half_y * sin_half_x * cos_half_z,
            cos_half_y * cos_half_x * cos_half_z + sin_half_y * sin_half_x * sin_half_z);
    }

    Mat4 to_mat4();

    static Quat slerp(Quat &a, const Quat &b, float t)
    {
        float cos_half_theta = a.dot(b);

        if (abs(cos_half_theta) >= 1.0f)
        {
            return a;
        }

        float half_theta = acos(cos_half_theta);
        float sin_half_theta = sqrt(1.0f - cos_half_theta * cos_half_theta);

        if (abs(sin_half_theta) < 0.001f)
        {
            return Quat(
                (a.i * 0.5f + b.i * 0.5f),
                (a.j * 0.5f + b.j * 0.5f),
                (a.k * 0.5f + b.k * 0.5f),
                (a.r * 0.5f + b.r * 0.5f));
        }

        float ratio_a = sin((1.0f - t) * half_theta) / sin_half_theta;
        float ratio_b = sin(t * half_theta) / sin_half_theta;

        return Quat(
            (a.i * ratio_a + b.i * ratio_b),
            (a.j * ratio_a + b.j * ratio_b),
            (a.k * ratio_a + b.k * ratio_b),
            (a.r * ratio_a + b.r * ratio_b));
    }

    Quat operator+(const Quat &b)
    {
        return Quat(i + b.i, j + b.j, k + b.k, r + b.r);
    }

    Quat operator-(const Quat &b)
    {
        return Quat(i - b.i, j - b.j, k - b.k, r - b.r);
    }

    Quat operator*(const Quat &b)
    {
        return Quat(
            i * b.r + j * b.k - k * b.j + r * b.i,
            -i * b.k + j * b.r + k * b.i + r * b.j,
            i * b.j - j * b.i + k * b.r + r * b.k,
            -i * b.i - j * b.j - k * b.k + r * b.r);
    }

    Quat operator*(float s)
    {
        return Quat(i * s, j * s, k * s, r * s);
    }

    Quat operator/(float s)
    {
        return Quat(i / s, j / s, k / s, r / s);
    }

    Vec4 operator*(const Vec4 &v)
    {
        Quat q = Quat(v.x, v.y, v.z, 0.0f);
        Quat result = q * conjugate();
        result = *this * result;
        return Vec4(result.i, result.j, result.k, 1.0f);
    }

    Vec3 operator*(const Vec3 &v)
    {
        Vec4 result = *this * Vec4(v.x, v.y, v.z, 1.0f);
        return Vec3(result.x, result.y, result.z);
    }

    Quat &operator+=(const Quat &other)
    {
        *this = *this + other;
        return *this;
    }

    Quat &operator-=(const Quat &other)
    {
        *this = *this - other;
        return *this;
    }

    Quat &operator*=(const Quat &other)
    {
        *this = *this * other;
        return *this;
    }

    Quat &operator*=(float s)
    {
        *this = *this * s;
        return *this;
    }

    Quat &operator/=(float s)
    {
        *this = *this / s;
        return *this;
    }

    bool operator==(const Quat &other) const
    {
        return i == other.i && j == other.j && k == other.k && r == other.r;
    }

    bool operator!=(const Quat &other) const
    {
        return !(*this == other);
    }

    float &operator[](int index)
    {
        return data[index];
    }

    const float &operator[](int index) const
    {
        return data[index];
    }
};