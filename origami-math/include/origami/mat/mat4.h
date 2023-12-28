#pragma once

#include <iostream>
#include <xmmintrin.h>
#include <origami/vec/vec.h>

class Mat4
{
public:
    float data[16];

    Mat4()
    {
        for (int i = 0; i < 16; i++)
        {
            data[i] = 0.0f;
        }
    };

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

    static Mat4 identity()
    {
        return Mat4(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    void print()
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

    static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);

    static Mat4 perspective(float fov, float aspect, float near, float far);
};
