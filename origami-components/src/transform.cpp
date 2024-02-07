
#include <origami/math.hpp>
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

Mat4 Transform::get_inverse_matrix() const
{
    return get_matrix().inverse();
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

void Transform::look_at(const Vec3 &target, const Vec3 &up)
{
    rotation = Quat::look_at(position, target, up);
}

Vec3 Transform::forward()
{
    return rotation * Vec3(0, 0, 1);
}

Vec3 Transform::right()
{
    return rotation * Vec3(1, 0, 0);
}

Vec3 Transform::up()
{
    return rotation * Vec3(0, 1, 0);
}