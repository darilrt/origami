#pragma once

#include <cmath>

#include "origami/vec/vec3.hpp"
#include "origami/vec/vec4.hpp"

class Mat4;

class Quat
{
public:
    float i, j, k, r;

    Quat(float value)
    {
        i = value;
        j = value;
        k = value;
        r = value;
    }

    Quat(float i, float j, float k, float r)
    {
        this->i = i;
        this->j = j;
        this->k = k;
        this->r = r;
    }

    Quat()
    {
        i = 0.0f;
        j = 0.0f;
        k = 0.0f;
        r = 1.0f;
    }

    Quat normalize() const
    {
        float length = sqrt(i * i + j * j + k * k + r * r);
        return Quat(i / length, j / length, k / length, r / length);
    }

    Quat conjugate() const
    {
        return Quat(-i, -j, -k, r);
    }

    Quat inverse() const
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

    static Quat from_axis_angle(const Vec3 &axis, float angle);

    static Quat from_euler(const Vec3 &euler);

    static Quat look_at(const Vec3 &from, const Vec3 &to, const Vec3 &up);

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
};