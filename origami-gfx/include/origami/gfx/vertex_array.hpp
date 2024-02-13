#pragma once

#include "origami/gfx/gfx_defs.hpp"
#include "origami/gfx/buffer.hpp"

class VertexArray
{
public:
    glid_t _id;

    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();

    void set_attribute(Buffer &buffer, size_t index, size_t size, size_t stride, size_t offset);
    void set_index_buffer(Buffer &buffer);
};