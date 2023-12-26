#pragma once

#include <xmmintrin.h>
#include <origami/vec/vec.h>

class Mat4
{
public:
    float data[16];

    union
    {
        struct
        {
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        };
        struct
        {
            float m0[4];
            float m1[4];
            float m2[4];
            float m3[4];
        };
        struct
        {
            float m[4][4];
        };
        struct
        {
            __m128 row[4];
        };
    };

    Mat4(float value)
    {
        for (int i = 0; i < 16; i++)
        {
            data[i] = value;
        }
    }

    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33)
    {
        data[0] = m00;
        data[1] = m01;
        data[2] = m02;
        data[3] = m03;
        data[4] = m10;
        data[5] = m11;
        data[6] = m12;
        data[7] = m13;
        data[8] = m20;
        data[9] = m21;
        data[10] = m22;
        data[11] = m23;
        data[12] = m30;
        data[13] = m31;
        data[14] = m32;
        data[15] = m33;
    }

    Mat4(const Mat4 &other)
    {
        for (int i = 0; i < 16; i++)
        {
            data[i] = other.data[i];
        }
    }

    __m128 col(int i) const
    {
        return _mm_set_ps(m3[i], m2[i], m1[i], m0[i]);
    }

    Mat4 transpose() const
    {
        Mat4 result = Mat4(0.0f);

        for (int i = 0; i < 4; i++)
        {
            result.row[i] = col(i);
        }
        return result;
    }

    static Mat4 identity()
    {
        return Mat4(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Mat4 translate(const Vec3 &v)
    {
        return Mat4(1.0f, 0.0f, 0.0f, v.x,
                    0.0f, 1.0f, 0.0f, v.y,
                    0.0f, 0.0f, 1.0f, v.z,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Mat4 scale(const Vec3 &v)
    {
        return Mat4(v.x, 0.0f, 0.0f, 0.0f,
                    0.0f, v.y, 0.0f, 0.0f,
                    0.0f, 0.0f, v.z, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Mat4 rotate(float angle, const Vec3 &v)
    {
        float c = cos(angle);
        float s = sin(angle);
        float x = v.x;
        float y = v.y;
        float z = v.z;

        return Mat4(x * x * (1.0f - c) + c, x * y * (1.0f - c) - z * s, x * z * (1.0f - c) + y * s, 0.0f,
                    y * x * (1.0f - c) + z * s, y * y * (1.0f - c) + c, y * z * (1.0f - c) - x * s, 0.0f,
                    x * z * (1.0f - c) - y * s, y * z * (1.0f - c) + x * s, z * z * (1.0f - c) + c, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);

    static Mat4 perspective(float fov, float aspect, float near, float far);

    Mat4 &operator=(const Mat4 &other)
    {
        for (int i = 0; i < 16; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }

    Mat4 operator*(const Mat4 &other) const
    {
        Mat4 result = Mat4(0.0f);

        for (int i = 0; i < 4; i++)
        {
            __m128 brod1 = _mm_set1_ps(m[i][0]);
            __m128 brod2 = _mm_set1_ps(m[i][1]);
            __m128 brod3 = _mm_set1_ps(m[i][2]);
            __m128 brod4 = _mm_set1_ps(m[i][3]);
            __m128 row = _mm_add_ps(
                _mm_add_ps(
                    _mm_mul_ps(brod1, other.row[0]),
                    _mm_mul_ps(brod2, other.row[1])),
                _mm_add_ps(
                    _mm_mul_ps(brod3, other.row[2]),
                    _mm_mul_ps(brod4, other.row[3])));
            result.row[i] = row;
        }
        return result;
    }

    Mat4 &operator*=(const Mat4 &other)
    {
        *this = *this * other;
        return *this;
    }

    Mat4 operator+(const Mat4 &other) const
    {
        Mat4 result = Mat4(0.0f);

        for (int i = 0; i < 4; i++)
        {
            result.row[i] = _mm_add_ps(row[i], other.row[i]);
        }
        return result;
    }

    Mat4 &operator+=(const Mat4 &other)
    {
        *this = *this + other;
        return *this;
    }

    Mat4 operator-(const Mat4 &other) const
    {
        Mat4 result = Mat4(0.0f);

        for (int i = 0; i < 4; i++)
        {
            result.row[i] = _mm_sub_ps(row[i], other.row[i]);
        }
        return result;
    }

    Mat4 &operator-=(const Mat4 &other)
    {
        *this = *this - other;
        return *this;
    }

    Mat4 operator*(float scalar) const
    {
        Mat4 result = Mat4(0.0f);

        for (int i = 0; i < 4; i++)
        {
            result.row[i] = _mm_mul_ps(row[i], _mm_set1_ps(scalar));
        }
        return result;
    }

    Mat4 &operator*=(float scalar)
    {
        *this = *this * scalar;
        return *this;
    }
};