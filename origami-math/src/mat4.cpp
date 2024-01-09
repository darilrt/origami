#include <iostream>
#include <xmmintrin.h>

#include "origami/mat/mat4.hpp"
#include "origami/quat/quat.hpp"

Mat4::Mat4()
{
    data[0] = 0.0f;
    data[1] = 0.0f;
    data[2] = 0.0f;
    data[3] = 0.0f;
    data[4] = 0.0f;
    data[5] = 0.0f;
    data[6] = 0.0f;
    data[7] = 0.0f;
    data[8] = 0.0f;
    data[9] = 0.0f;
    data[10] = 0.0f;
    data[11] = 0.0f;
    data[12] = 0.0f;
    data[13] = 0.0f;
    data[14] = 0.0f;
    data[15] = 0.0f;
}

Mat4::Mat4(float m00, float m01, float m02, float m03,
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

void Mat4::print()
{
    for (int i, j = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            std::cout << data[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
}

Mat4 Mat4::inverse()
{
    Mat4 result{};

    float det = determinant();

    if (det == 0.0f)
        return result;

    Mat4 cofactor_matrix = cofactor();
    Mat4 transpose_matrix = cofactor_matrix.transpose();

    for (int i = 0; i < 16; i++)
        result.data[i] = transpose_matrix.data[i] / det;

    return result;
}

Mat4 Mat4::transpose()
{
    return Mat4(data[0], data[4], data[8], data[12],
                data[1], data[5], data[9], data[13],
                data[2], data[6], data[10], data[14],
                data[3], data[7], data[11], data[15]);
}

Mat4 Mat4::cofactor()
{
    Mat4 result{};

    for (int i = 0; i < 4; i++)
    {
        int sign = (i % 2 == 0) ? 1 : -1;

        for (int j = 0; j < 4; j++)
        {
            int index = i * 4 + j;
            int index_cofactor = (i + 1) % 4 * 4 + (j + 1) % 4;

            result.data[index] = sign * data[index_cofactor];
            sign *= -1;
        }
    }

    return result;
}

float Mat4::determinant()
{
    float det = 0.0f;

    for (int i = 0; i < 4; i++)
    {
        int sign = (i % 2 == 0) ? 1 : -1;

        int index = i;
        int index_cofactor = (i + 1) % 4;

        float cofactor = sign * data[index_cofactor];
        sign *= -1;

        for (int j = 0; j < 3; j++)
        {
            index += 4;
            index_cofactor = (index_cofactor + 1) % 4;

            cofactor *= data[index_cofactor];
            sign *= -1;
        }

        det += cofactor;
    }

    return det;
}

void Mat4::translate(Vec3 translation)
{
    data[12] += translation.x;
    data[13] += translation.y;
    data[14] += translation.z;
}

Mat4 Mat4::identity()
{
    return Mat4(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.f);
}

void Mat4::rotate(Quat rotation)
{
    Mat4 rotation_matrix = rotation.to_mat4();
    *this = rotation_matrix * *this;
}

void Mat4::scale(Vec3 scale)
{
    data[0] *= scale.x;
    data[5] *= scale.y;
    data[10] *= scale.z;
}

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far)
{
    Mat4 result = Mat4::identity();

    result.data[0] = 2.0f / (right - left);
    result.data[5] = 2.0f / (top - bottom);
    result.data[10] = -2.0f / (far - near);
    result.data[12] = -(right + left) / (right - left);
    result.data[13] = -(top + bottom) / (top - bottom);
    result.data[14] = -(far + near) / (far - near);

    return result;
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far)
{
    float s = 1.0f / tan(fov / 2.0f);

    Mat4 result = Mat4::identity();

    result.data[0] = s / aspect;
    result.data[5] = s;
    result.data[10] = -far / (far - near);
    result.data[14] = -(far * near) / (far - near);

    result.data[11] = -1.0f;
    result.data[15] = 0.0f;

    return result;
}

Mat4 Mat4::operator+(const Mat4 &other)
{
    Mat4 result{};

    __m128 row_0 = _mm_load_ps(data);
    __m128 row_1 = _mm_load_ps(data + 4);
    __m128 row_2 = _mm_load_ps(data + 8);
    __m128 row_3 = _mm_load_ps(data + 12);

    __m128 row_0_other = _mm_load_ps(other.data);
    __m128 row_1_other = _mm_load_ps(other.data + 4);
    __m128 row_2_other = _mm_load_ps(other.data + 8);
    __m128 row_3_other = _mm_load_ps(other.data + 12);

    _mm_store_ps(result.data, _mm_add_ps(row_0, row_0_other));
    _mm_store_ps(result.data + 4, _mm_add_ps(row_1, row_1_other));
    _mm_store_ps(result.data + 8, _mm_add_ps(row_2, row_2_other));
    _mm_store_ps(result.data + 12, _mm_add_ps(row_3, row_3_other));

    return result;
}

Mat4 Mat4::operator*(const Mat4 &other)
{
    Mat4 result{};

    __m128 row_0 = _mm_load_ps(data);
    __m128 row_1 = _mm_load_ps(data + 4);
    __m128 row_2 = _mm_load_ps(data + 8);
    __m128 row_3 = _mm_load_ps(data + 12);

    for (int i = 0; i < 4; i++)
    {
        __m128 brod_0 = _mm_set1_ps(other.data[4 * i + 0]);
        __m128 brod_1 = _mm_set1_ps(other.data[4 * i + 1]);
        __m128 brod_2 = _mm_set1_ps(other.data[4 * i + 2]);
        __m128 brod_3 = _mm_set1_ps(other.data[4 * i + 3]);
        __m128 row = _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(brod_0, row_0),
                _mm_mul_ps(brod_1, row_1)),
            _mm_add_ps(
                _mm_mul_ps(brod_2, row_2),
                _mm_mul_ps(brod_3, row_3)));
        _mm_store_ps(&result.data[4 * i], row);
    }
    return result;
}

Vec4 Mat4::operator*(const Vec4 &other)
{
    Vec4 result{};

    __m128 row_0 = _mm_load_ps(data);
    __m128 row_1 = _mm_load_ps(data + 4);
    __m128 row_2 = _mm_load_ps(data + 8);
    __m128 row_3 = _mm_load_ps(data + 12);

    __m128 brod_0 = _mm_set1_ps(other.x);
    __m128 brod_1 = _mm_set1_ps(other.y);
    __m128 brod_2 = _mm_set1_ps(other.z);
    __m128 brod_3 = _mm_set1_ps(other.w);

    __m128 row = _mm_add_ps(
        _mm_add_ps(
            _mm_mul_ps(brod_0, row_0),
            _mm_mul_ps(brod_1, row_1)),
        _mm_add_ps(
            _mm_mul_ps(brod_2, row_2),
            _mm_mul_ps(brod_3, row_3)));

    _mm_store_ps(&result.x, row);

    return result;
}