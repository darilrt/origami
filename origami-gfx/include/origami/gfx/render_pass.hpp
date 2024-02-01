#pragma once

#include <vector>
#include <stdexcept>
#include <cstdint>

struct Attachment
{
    uint32_t id;
    uint32_t format = 37;
    uint32_t samples = 1;
    uint32_t load_op = 1;
    uint32_t store_op = 0;
    uint32_t stencil_load_op = 2;
    uint32_t stencil_store_op = 1;
    uint32_t initial_layout = 0;
    uint32_t final_layout = 1000001002;
    uint32_t layout = 2;
};

class RenderPass
{
public:
    void *id = 0;
    void *device = 0;

    struct Parameters
    {
        void *device;
        std::vector<Attachment> attachments;
    };

    RenderPass() = default;

    static RenderPass create(const Parameters &description);
};
