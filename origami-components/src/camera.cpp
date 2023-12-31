#include "origami/components/camera.hpp"

void Camera::start(EngineState &state)
{
    auto &graphics = state.get_resource<GraphicsSystem>();

    render_pass = graphics.create_render_pass((float)resolution.x, (float)resolution.y);
}

void Camera::set_orthographic(float size, float aspect, float, float)
{
    is_orhographic = true;

    float half_width = size * aspect / 2.0f;
    float half_height = size / 2.0f;

    render_pass->projection = Mat4::ortho(-half_width, half_width, -half_height, half_height, -1.0f, 1.0f);
}

void Camera::set_perspective(float fov, float aspect, float, float)
{
    is_orhographic = false;

    render_pass->projection = Mat4::perspective(fov, aspect, 0.1f, 100.0f);
}
