#pragma once

#include <origami.hpp>

class Transform
{
public:
    Transform *parent = nullptr;
    Vec3 position;
    Quat rotation;
    Vec3 scale;

    Transform() : position(Vec3(0.0f)), rotation(Quat::identity()), scale(Vec3(1.0)) {}
    Transform(const Vec3 &position, const Quat &rotation, const Vec3 &scale) : position(position), rotation(rotation), scale(scale) {}

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
