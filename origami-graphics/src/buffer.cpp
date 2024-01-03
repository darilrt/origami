#include "origami/graphics/buffer.hpp"

Buffer::Buffer(Type type, Usage usage)
{
    this->size = 0;
    this->type = type;
    this->usage = usage;

    buffer = {SG_INVALID_ID};
};

Buffer::~Buffer()
{
    sg_destroy_buffer(buffer);
}

void Buffer::set_data(const void *data, size_t size)
{
    this->size = size;

    if (buffer.id == SG_INVALID_ID)
    {
        if (usage == Usage::Static)
            buffer = sg_make_buffer(sg_buffer_desc{
                .type = static_cast<sg_buffer_type>(type),
                .usage = static_cast<sg_usage>(usage),
                .data = {data, size},
            });
        else
        {
            buffer = sg_make_buffer(sg_buffer_desc{
                .size = size,
                .type = static_cast<sg_buffer_type>(type),
                .usage = static_cast<sg_usage>(usage),
            });
            sg_update_buffer(buffer, {data, size});
        }
    }
    else
    {
        sg_update_buffer(buffer, {data, size});
    }
}
