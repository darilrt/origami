#include "origami/quat/quat.hpp"
#include "origami/mat/mat4.hpp"
#include "origami/math/const.hpp"

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

Quat Quat::from_axis_angle(const Vec3 &axis, float angle)
{
    float half_angle = angle / 2.0f;
    float s = sin(half_angle);
    return Quat(axis.x * s, axis.y * s, axis.z * s, cos(half_angle));
}

Quat Quat::look_at(const Vec3 &from, const Vec3 &to, const Vec3 &up)
{
    Vec3 forward = (to - from).normalize();
    Vec3 right = forward.cross(up).normalize();
    Vec3 new_up = right.cross(forward).normalize();

    float w = sqrt(1.0f + right.x + new_up.y + forward.z) / 2.0f;
    float w4_recip = 1.0f / (4.0f * w);
    return Quat(
        (new_up.z - forward.y) * w4_recip,
        (forward.x - right.z) * w4_recip,
        (right.y - new_up.x) * w4_recip,
        w);
}