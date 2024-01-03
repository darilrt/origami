#include "origami/components/camera.hpp"

void Camera::start(EngineState &state)
{
    auto &graphics = state.get_resource<GraphicsSystem>();
    render_pass = graphics.create_render_pass((int)resolution.x, (int)resolution.y);
}

void Camera::update(EngineState &state, const Update &time)
{
    if (!render_pass)
        throw std::runtime_error("Camera not initialized, call Camera::start() first");

    render_pass->view = transform.get_inverse_matrix();
}

void Camera::set_orthographic(float size, float aspect, float near, float far)
{
    if (!render_pass)
        throw std::runtime_error("Camera not initialized, call Camera::start() first");

    is_orhographic = true;
    this->size = size;
    this->near = near;
    this->far = far;

    float half_width = size * aspect / 2.0f;
    float half_height = size / 2.0f;

    render_pass->projection = Mat4::ortho(-half_width, half_width, -half_height, half_height, near, far);
}

void Camera::set_perspective(float fov, float aspect, float near, float far)
{
    if (!render_pass)
        throw std::runtime_error("Camera not initialized, call Camera::start() first");

    is_orhographic = false;
    this->size = fov;
    this->near = near;
    this->far = far;

    render_pass->projection = Mat4::perspective(fov, aspect, near, far);
}

void Camera::set_resolution(Vec2 _resolution)
{
    if (!render_pass)
        throw std::runtime_error("Camera not initialized, call Camera::start() first");

    resolution = _resolution;
    float aspect = _resolution.x / _resolution.y;

    render_pass->resize((float)resolution.x, (float)resolution.y);

    if (is_orhographic)
    {
        float half_width = size * aspect / 2.0f;
        float half_height = size / 2.0f;

        render_pass->projection = Mat4::ortho(-half_width, half_width, -half_height, half_height, near, far);
    }
    else
    {
        render_pass->projection = Mat4::perspective(size, aspect, near, far);
    }
}

void Camera::set_active(EngineState &state)
{
    if (!render_pass)
        throw std::runtime_error("Camera not initialized, call Camera::start() first");

    static auto &graphics = state.get_resource<GraphicsSystem>();
    graphics.set_render_pass(render_pass);
}

Vec2 Camera::screen_to_world2d(Vec2 pos, Vec2 window_resolution)
{
    if (!render_pass)
        throw std::runtime_error("Camera not initialized, call Camera::start() first");

    float aspect = window_resolution.x / window_resolution.y;
    Vec2 npos = pos / window_resolution * 2.0f - 1.0f;
    npos.y *= -1.0f;

    if (is_orhographic)
    {
        float half_width = size * aspect / 2.0f;
        float half_height = size / 2.0f;

        npos.x *= half_width;
        npos.y *= half_height;
    }
    else
    {
        float half_width = near * tan(size / 2.0f);
        float half_height = half_width / aspect;

        npos.x *= half_width;
        npos.y *= half_height;
    }

    Vec4 rpos = transform.get_matrix() * Vec4(npos.x, npos.y, 0.0f, 1.0f);

    return Vec2(rpos.x, rpos.y);
}