#pragma once

#include <origami/core.hpp>

class Buffer
{
public:
    enum Usage
    {
        Static,
        Dynamic,
        Stream,
    };

    enum Type
    {
        Default,
        Vertex,
        Index,
    };

    Buffer(Type type = Default, Usage usage = Static);

    ~Buffer();

    void set_data(const void *data, size_t size);

private:
    Type type;
    Usage usage;
};