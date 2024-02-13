#include "GL/glew.hpp"
#include <GL/gl.h>

#include "origami/gfx/buffer.hpp"

Buffer::Buffer(BufferType type) : type(type)
{
    GL_CALL(glGenBuffers(1, &_id));
}

Buffer::~Buffer()
{
    GL_CALL(glDeleteBuffers(1, &_id));
}

void Buffer::bind()
{
    GL_CALL(glBindBuffer(static_cast<GLenum>(type), _id));
}

void Buffer::unbind()
{
    GL_CALL(glBindBuffer(static_cast<GLenum>(type), 0));
}

void Buffer::set_data(const void *data, size_t size, BufferUsage usage)
{
    bind();
    GL_CALL(glBufferData(static_cast<GLenum>(type), size, data, static_cast<GLenum>(usage)));
    unbind();
}

void Buffer::set_sub_data(const void *data, size_t size, size_t offset)
{
    bind();
    GL_CALL(glBufferSubData(static_cast<GLenum>(type), offset, size, data));
    unbind();
}
