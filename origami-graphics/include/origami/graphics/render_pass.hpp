#pragma once

#include <origami/core.hpp>
#include <sokol_gfx.h>

#include "origami/graphics/texture.hpp"

class RenderPass
{
public:
    Shared<Image> *color_attachment = nullptr;

    sg_pass_action action;
};