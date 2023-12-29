#pragma once

#include <origami.hpp>

class Transform
{
public:
    Transform *parent = nullptr;
    Vec3 position;
    Quat rotation = Quat::identity();
    Vec3 scale = Vec3(1.0f);

    Mat4 get_matrix() const
    {
        Mat4 matrix = Mat4::identity();
        matrix.translate(position);
        matrix.rotate(rotation);
        matrix.scale(scale);

        if (parent)
            matrix = parent->get_matrix() * matrix;

        return matrix;
    }
};
