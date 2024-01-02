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

    if (!render_pass)
        return;

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

    if (!render_pass)
        return;

    render_pass->projection = Mat4::perspective(fov, aspect, near, far);
}

void Camera::set_resolution(Vec2 _resolution)
{
    if (!render_pass)
        throw std::runtime_error("Camera not initialized, call Camera::start() first");

    resolution = _resolution;
    float aspect = _resolution.x / _resolution.y;

    if (!render_pass)
        return;

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