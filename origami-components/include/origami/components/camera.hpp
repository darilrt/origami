#pragma once

#include <origami/core.hpp>
#include <origami/graphics.hpp>
#include <origami/window.hpp>

#include "origami/components/transform.hpp"

class Camera
{
public:
    Transform transform;

    void start(EngineState &state);

    void update(EngineState &state, const Update &time);

    void set_orthographic(float size, float aspect, float near, float far);

    void set_perspective(float fov, float aspect, float near, float far);

    void set_resolution(Vec2 size);

    inline void set_clear_color(Vec4 color) { render_pass->clear_color = color; }

    void set_active(EngineState &state);

    Vec2 screen_to_world2d(Vec2 pos, Vec2 window_resolution);

private:
    bool is_orhographic = false;
    Shared<RenderPass> render_pass;
    Vec2 resolution = {1.0, 1.0};

    float size;
    float near;
    float far;
};