#pragma once

#include <origami/core.hpp>
#include <sokol_gfx.h>

class Buffer
{
public:
    enum Usage
    {
        Static = SG_USAGE_IMMUTABLE,
        Dynamic = SG_USAGE_DYNAMIC,
        Stream = SG_USAGE_STREAM,
    };

    enum Type
    {
        Default = _SG_BUFFERTYPE_DEFAULT,
        Vertex = SG_BUFFERTYPE_VERTEXBUFFER,
        Index = SG_BUFFERTYPE_INDEXBUFFER,
    };

    sg_buffer buffer;
    size_t size;

    Buffer(Type type = Default, Usage usage = Static);

    ~Buffer();

    void set_data(const void *data, size_t size);

private:
    Type type;
    Usage usage;
};