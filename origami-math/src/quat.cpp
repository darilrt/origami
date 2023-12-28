#include "origami/quat/quat.hpp"
#include "origami/mat/mat4.hpp"

Mat4 Quat::to_mat4()
{
    return Mat4(
        1.0f - 2.0f * j * j - 2.0f * k * k, 2.0f * i * j - 2.0f * k * r, 2.0f * i * k + 2.0f * j * r, 0.0f,
        2.0f * i * j + 2.0f * k * r, 1.0f - 2.0f * i * i - 2.0f * k * k, 2.0f * j * k - 2.0f * i * r, 0.0f,
        2.0f * i * k - 2.0f * j * r, 2.0f * j * k + 2.0f * i * r, 1.0f - 2.0f * i * i - 2.0f * j * j, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}