#pragma once

#include <origami/core.hpp>
#include <origami/graphics.hpp>
#include <origami/window.hpp>

#include "origami/components/transform.hpp"

class Camera
{
public:
    Transform transform;
    Hook<Vec2> resolution = Hook<Vec2>({1, 1});

    void start(EngineState &state);

    void update(EngineState &state, const Update &time);

    void set_orthographic(float size, float aspect, float near, float far);

    void set_perspective(float fov, float aspect, float near, float far);

    inline void set_clear_color(Vec4 color) { render_pass->clear_color = color; }

    void set_active(EngineState &state);

private:
    bool is_orhographic = false;
    Shared<RenderPass> render_pass;
};