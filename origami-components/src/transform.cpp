#include "origami/components/transform.hpp"

Mat4 Transform::get_matrix() const
{
    Mat4 matrix = Mat4::identity();
    matrix.scale(scale);
    matrix.rotate(rotation);
    matrix.translate(position);

    if (parent)
        matrix = parent->get_matrix() * matrix;

    return matrix;
}

Mat4 Transform2D::get_matrix() const
{
    Mat4 matrix = Mat4::identity();
    matrix.scale(Vec3(scale.x, scale.y, 1.0f));
    matrix.rotate(Quat::from_euler({0.0f, 0.0f, rotation}));
    matrix.translate(Vec3(position.x, position.y, depth));

    if (parent)
        matrix = parent->get_matrix() * matrix;

    return matrix;
}