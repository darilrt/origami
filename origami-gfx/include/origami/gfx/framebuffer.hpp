#pragma once

#include <origami/core.hpp>
#include <origami/gfx/gfx_defs.hpp>

enum class FramebufferAttachment : uint32_t
{
    COLOR0 = 0x8CE0,
    COLOR1 = 0x8CE1,
    COLOR2 = 0x8CE2,
    COLOR3 = 0x8CE3,
    COLOR4 = 0x8CE4,
    COLOR5 = 0x8CE5,
    COLOR6 = 0x8CE6,
    COLOR7 = 0x8CE7,
    DEPTH = 0x8D00,
    STENCIL = 0x8D20,
    DEPTH_STENCIL = 0x821A
};

class Framebuffer
{
public:
    glid_t _id;
    int _width;
    int _height;

    Framebuffer(int width, int height);

    ~Framebuffer();

    void bind();

    void unbind();

    void attach_texture(glid_t texture, FramebufferAttachment attachment);
};