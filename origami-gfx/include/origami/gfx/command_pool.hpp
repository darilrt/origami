#pragma once

#include <cstdint>

#include "command_buffer.hpp"

class CommandPool
{
public:
    void *id = 0;
    void *device = 0;

    struct Parameters
    {
        void *device = 0;
        uint32_t flags = 0;
        uint32_t queue_family_index = 0;
    };

    CommandPool() = default;

    CommandPool(const Parameters &parameters);

    void destroy();

    void reset();

    CommandBuffer allocate_command_buffer();
};