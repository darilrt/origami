#include "GL/glew.hpp"
#include <GL/gl.h>

#include "origami/gfx/framebuffer.hpp"

Framebuffer::Framebuffer(int width, int height)
{
    glGenFramebuffers(1, &_id);
    bind();
    _width = width;
    _height = height;
    unbind();
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &_id);
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attach_texture(glid_t texture, FramebufferAttachment attachment)
{
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, (uint32_t)attachment, GL_TEXTURE_2D, texture, 0);
    unbind();
}