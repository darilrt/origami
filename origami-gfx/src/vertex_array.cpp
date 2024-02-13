#include "GL/glew.hpp"
#include <GL/gl.h>

#include "origami/gfx/vertex_array.hpp"

VertexArray::VertexArray()
{
    GL_CALL(glGenVertexArrays(1, &_id));
}

VertexArray::~VertexArray()
{
    GL_CALL(glDeleteVertexArrays(1, &_id));
}

void VertexArray::bind()
{
    GL_CALL(glBindVertexArray(_id));
}

void VertexArray::unbind()
{
    GL_CALL(glBindVertexArray(0));
}

#include <iostream>

void VertexArray::set_attribute(Buffer &buffer, size_t index, size_t size, size_t stride, size_t offset)
{
    bind();
    buffer.bind();
    GL_CALL(glEnableVertexAttribArray(index));
    GL_CALL(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void *)offset));
    buffer.unbind();
    unbind();
}

void VertexArray::set_index_buffer(Buffer &buffer)
{
    bind();
    buffer.bind();
    unbind();
}