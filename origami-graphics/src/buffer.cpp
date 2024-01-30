#include "origami/graphics/buffer.hpp"

Buffer::Buffer(Type type, Usage usage)
{
    this->type = type;
    this->usage = usage;
};

Buffer::~Buffer()
{
}

void Buffer::set_data(const void *data, size_t size)
{
}
