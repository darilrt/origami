#pragma once

#include <origami/graphics.hpp>

#include "origami/components/transform.hpp"

class Camera
{
public:
    Transform transform;
    Vec2 resolution = {1, 1};

    void start(EngineState &state);

    void set_orthographic(float size, float aspect, float near, float far);

    void set_perspective(float fov, float aspect, float near, float far);

private:
    bool is_orhographic = false;
    Shared<RenderPass> render_pass;
};