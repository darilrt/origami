
#include "origami/mat/mat4.h"

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
    float f = 1.0f / tan(fov / 2.0f);

    return Mat4(f / aspect, 0.0f, 0.0f, 0.0f,
                0.0f, f, 0.0f, 0.0f,
                0.0f, 0.0f, (far + near) / (near - far), (2.0f * far * near) / (near - far),
                0.0f, 0.0f, -1.0f, 0.0f);
}