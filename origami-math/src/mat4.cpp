
#include "origami/mat/mat4.h"

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far)
{
    Mat4 result(1.0f);

    result.m00 = 2.0f / (right - left);
    result.m11 = 2.0f / (top - bottom);
    result.m22 = -2.0f / (far - near);
    result.m30 = -(right + left) / (right - left);
    result.m31 = -(top + bottom) / (top - bottom);
    result.m32 = -(far + near) / (far - near);

    return result;
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far)
{
    float f = 1.0f / tan(fov / 2.0f);

    return Mat4(f / aspect, 0.0f, 0.0f, 0.0f,
                0.0f, f, 0.0f, 0.0f,
                0.0f, 0.0f, (far + near) / (near - far), (2.0f * far * near) / (near - far),
                0.0f, 0.0f, -1.0f, 0.0f);
}