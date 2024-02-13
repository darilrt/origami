#pragma once

#include "origami/gfx/gfx_defs.hpp"

enum class BufferType
{
    Array = 0x8892,
    ElementArray = 0x8893,
    Uniform = 0x8A11,
    ShaderStorage = 0x90D2
};

enum class BufferUsage
{
    Static = 0x88E4,
    Dynamic = 0x88E8,
    Stream = 0x88E0
};

class Buffer
{
public:
    glid_t _id;
    BufferType type;

    Buffer(BufferType type);
    ~Buffer();

    void bind();
    void unbind();

    void set_data(const void *data, size_t size, BufferUsage usage);
    void set_sub_data(const void *data, size_t size, size_t offset);
};