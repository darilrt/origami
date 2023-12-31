#pragma once

#include <origami/core.hpp>
#include <sokol_gfx.h>

#include "origami/graphics/texture.hpp"

class RenderPass
{
public:
    Vec4 clear_color = {0.1f, 0.1f, 0.1f, 1.0f};
    Mat4 view;
    Mat4 projection;
    Shared<Image> color_attachment = nullptr;
    Shared<Image> depth_attachment = nullptr;

    sg_pass_action action;
    sg_pass pass;

    RenderPass(int width, int height);

    ~RenderPass();

    void resize(int width, int height);
};