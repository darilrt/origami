#pragma once

#include "origami/vec/vec.hpp"

class Quat;

class Mat4
{
public:
    float data[16];

    Mat4();

    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33);

    void print();

    Mat4 inverse();

    Mat4 transpose();

    Mat4 cofactor();

    float determinant();

    void translate(Vec3 translation);

    void rotate(Quat rotation);

    void scale(Vec3 scale);

    static Mat4 identity();

    static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);

    static Mat4 perspective(float fov, float aspect, float near, float far);

    Mat4 operator+(const Mat4 &other);

    Mat4 operator*(const Mat4 &other);

    Vec4 operator*(const Vec4 &other);
};
