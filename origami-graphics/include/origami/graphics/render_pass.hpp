#pragma once

#include <origami/core.hpp>

#include "origami/graphics/texture.hpp"

class RenderPass
{
public:
    Vec4 clear_color = {0.1f, 0.1f, 0.1f, 1.0f};
    Mat4 view;
    Mat4 projection;
    bool enabled = true;

    Unique<Framebuffer> _framebuffer;
    Shared<Texture> color_texture;
    Shared<Texture> depth_texture;

    RenderPass(int width, int height);

    ~RenderPass();

    void resize(int width, int height);

    void set_clear_color(Vec4 color);

    void begin();

    void end();
};