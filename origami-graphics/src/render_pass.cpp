#include <GL/glew.hpp>
#include <GL/gl.h>
#include <origami/math.hpp>
#include <origami/gfx.hpp>

#include "origami/graphics/render_pass.hpp"

RenderPass::RenderPass(int width, int height)
{
    _framebuffer = std::make_unique<Framebuffer>(width, height);
    resize(width, height);
}

RenderPass::~RenderPass()
{
}

void RenderPass::resize(int width, int height)
{
    color_texture = std::make_shared<Texture>(width, height, TextureFormat::RGBA);
    depth_texture = std::make_shared<Texture>(width, height, TextureFormat::Depth);

    _framebuffer->attach_texture(color_texture->_id, FramebufferAttachment::COLOR0);
    _framebuffer->attach_texture(depth_texture->_id, FramebufferAttachment::DEPTH);
}

void RenderPass::set_clear_color(Vec4 color)
{
    this->clear_color = color;
}

void RenderPass::begin()
{
    GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer->_id));
}

void RenderPass::end()
{
    GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
}