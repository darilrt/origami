#include "origami/quat/quat.hpp"
#include "origami/mat/mat4.hpp"

Mat4 Quat::to_mat4()
{
    return Mat4(
        1.0f - 2.0f * j * j - 2.0f * k * k,
        2.0f * i * j - 2.0f * k * r,
        2.0f * i * k + 2.0f * j * r,
        0.0f,
        2.0f * i * j + 2.0f * k * r,
        1.0f - 2.0f * i * i - 2.0f * k * k,
        2.0f * j * k - 2.0f * i * r,
        0.0f,
        2.0f * i * k - 2.0f * j * r,
        2.0f * j * k + 2.0f * i * r,
        1.0f - 2.0f * i * i - 2.0f * j * j,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f);
}

Quat Quat::from_euler(const Vec3 &euler)
{
    double c1 = cos(euler.x / 2.0);
    double c2 = cos(euler.y / 2.0);
    double c3 = cos(euler.z / 2.0);
    double s1 = sin(euler.x / 2.0);
    double s2 = sin(euler.y / 2.0);
    double s3 = sin(euler.z / 2.0);

    return Quat(
        s1 * c2 * c3 + c1 * s2 * s3,
        c1 * s2 * c3 - s1 * c2 * s3,
        c1 * c2 * s3 + s1 * s2 * c3,
        c1 * c2 * c3 - s1 * s2 * s3);
}