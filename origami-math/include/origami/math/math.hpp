#pragma once

#include "origami/vec/vec.hpp"
#include "origami/quat/quat.hpp"
#include "origami/mat/mat4.hpp"

#include <cmath>

namespace math
{
    // Returns the linear interpolation between a and b at time t
    // example:
    // ```c++
    // float lerped = math::lerp(0.0f, 1.0f, 0.5f);
    // lerped == 0.5f // true
    // ```
    template <typename T>
    T lerp(T a, T b, float t)
    {
        return a + (b - a) * t;
    }

    // Returns the value clamped between min and max
    // example:
    // ```c++
    // float clamped = math::clamp(5.0f, 0.0f, 1.0f);
    // clamped == 1.0f // true
    // ```
    template <typename T>
    T clamp(T value, T min, T max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    template <typename T>
    T min(T a, T b)
    {
        return a < b ? a : b;
    }

    template <typename T>
    T max(T a, T b)
    {
        return a > b ? a : b;
    }

    template <typename T>
    T abs(T value)
    {
        return value < 0 ? -value : value;
    }

    template <typename T>
    T sign(T value)
    {
        return value < 0 ? -1 : 1;
    }

    template <typename T>
    T sqrt(T value)
    {
        return std::sqrt(value);
    }

    template <typename T>
    T pow(T value, T exponent)
    {
        return std::pow(value, exponent);
    }

    template <typename T>
    T sin(T value)
    {
        return std::sin(value);
    }

    template <typename T>
    T cos(T value)
    {
        return std::cos(value);
    }

    template <typename T>
    T tan(T value)
    {
        return std::tan(value);
    }

    template <typename T>
    T asin(T value)
    {
        return std::asin(value);
    }

    template <typename T>
    T acos(T value)
    {
        return std::acos(value);
    }

    // Returns the angle in radians between the positive x-axis and the ray from (0, 0) to (x, y)
    // example:
    // ```c++
    // float angle = math::atan(1.0f);
    // angle == 0.78539816339f // true
    // ```
    template <typename T>
    T atan(T value)
    {
        return std::atan(value);
    }

    // Returns the angle in radians between the positive x-axis and the ray from (0, 0) to (x, y)
    // example:
    // ```c++
    // float angle = math::atan2(1.0f, 1.0f);
    // angle == 0.78539816339f // true
    // ```
    template <typename T>
    T atan2(T y, T x)
    {
        return std::atan2(y, x);
    }

    // Returns the lowest integer less than or equal to a number
    // example:
    // ```c++
    // int floor = math::floor(1.5f);
    // floor == 1 // true
    template <typename T>
    T floor(T value)
    {
        return std::floor(value);
    }

    // Returns the smallest integer greater than or equal to a number
    // example:
    // ```c++
    // int ceiling = math::ceil(1.5f);
    // ceiling == 2 // true
    // ```
    template <typename T>
    T ceil(T value)
    {
        return std::ceil(value);
    }

    // Rounds a number to the nearest integer
    // example:
    // ```c++
    // int rounded = math::round(1.5f);
    // rounded == 2 // true
    // ```
    template <typename T>
    T round(T value)
    {
        return std::round(value);
    }

    // Returns the fractional part of a number
    // example:
    // ```c++
    // float fraction = math::frac(1.5f);
    // fraction == 0.5f // true
    // ```
    template <typename T>
    T frac(T value)
    {
        return value - floor(value);
    }

    // Returns the modulus of the value and the divisor
    // example:
    // ```c++
    // float remainder = math::mod(5.0f, 2.0f);
    // remainder == 1.0f // true
    // ```
    template <typename T>
    T mod(T value, T divisor)
    {
        return value - floor(value / divisor) * divisor;
    }

    // Takes a value in radians and returns a value in degrees
    // example:
    // ```c++
    // float radians = math::rad(90.0f);
    // radians == 1.57079632679f // true
    // ```
    template <typename T>
    T rad(T value)
    {
        return value * (T)0.01745329251;
    }

    // Takes a value in degrees and returns a value in radians
    // example:
    // ```c++
    // float degrees = math::deg(1.57079632679f);
    // degrees == 90.0f // true
    // ```
    template <typename T>
    T deg(T value)
    {
        return value * (T)57.2957795131;
    }

    template <typename T>
    T lerp_angle(T a, T b, float t)
    {
        T delta = mod(b - a, (T)360);
        if (delta > (T)180)
            delta -= (T)360;
        return a + delta * t;
    }

    template <typename T>
    T inverse_lerp(T a, T b, T value)
    {
        return (value - a) / (b - a);
    }

    template <typename T>
    T smoothstep(T a, T b, T value)
    {
        T t = clamp(inverse_lerp(a, b, value), (T)0, (T)1);
        return t * t * (3 - 2 * t);
    }
}
