#include <origami/math.hpp>

#include "origami/graphics/render_pass.hpp"

RenderPassOld::RenderPassOld(int width, int height)
{
    resize(width, height);
}

RenderPassOld::~RenderPassOld()
{
}

void RenderPassOld::resize(int width, int height)
{
}

void RenderPassOld::set_clear_color(Vec4 color)
{
    this->clear_color = color;
}

void RenderPassOld::begin()
{
}

void RenderPassOld::end()
{
}