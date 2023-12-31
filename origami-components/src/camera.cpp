#include "origami/components/camera.hpp"

void Camera::start(EngineState &state)
{
    auto &graphics = state.get_resource<GraphicsSystem>();

    render_pass = graphics.create_render_pass((float)resolution.get().x, (float)resolution.get().y);
    render_pass->view = transform.get_matrix();

    resolution.on_change = [&](const Vec2 _, const Vec2 new_resolution)
    {
        render_pass->resize(new_resolution.x, new_resolution.y);
    };
}

void Camera::update(EngineState &state, const Update &time)
{
    render_pass->view = transform.get_inverse_matrix();
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

void Camera::set_active(EngineState &state)
{
    static auto &graphics = state.get_resource<GraphicsSystem>();

    graphics.set_render_pass(render_pass);
}