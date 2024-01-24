#pragma once

#include <origami/core.hpp>
#include <sokol_gfx.h>

#include "origami/graphics/texture.hpp"

class RenderPassOld
{
public:
    Vec4 clear_color = {0.1f, 0.1f, 0.1f, 1.0f};
    Mat4 view;
    Mat4 projection;
    Shared<ImageOld> albedo_attachment;
    Shared<ImageOld> normal_ao_attachment;
    Shared<ImageOld> position_roughness_attachment;
    Shared<ImageOld> emissive_metallic_attachment;
    Shared<ImageOld> depth_attachment;

    sg_pass_action action;
    sg_pass pass;

    RenderPassOld(int width, int height);

    ~RenderPassOld();

    void resize(int width, int height);

    void set_clear_color(Vec4 color);

    void begin();

    void end();
};