#pragma once

#include <vector>

#include "pipeline.hpp"
#include "framebuffer.hpp"
#include "render_pass.hpp"

struct Viewport
{
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    float min_depth = 0.0f;
    float max_depth = 1.0f;
};

class CommandBuffer
{
public:
    void *id = 0;

    struct Parameters
    {
        void *device = 0;
        void *command_pool = 0;
        uint32_t level = 0;
    };

    // struct SubmitInfo
    // {
    //     void *queue = 0;
    //     uint32_t wait_semaphore_count = 0;
    //     void *wait_semaphores = nullptr;

    //     void *wait_stages = nullptr;

    //     std::vector<void *> command_buffers;

    //     uint32_t signal_semaphore_count = 0;
    //     void *signal_semaphores = nullptr;

    //     void *fence = 0;
    // };

    CommandBuffer() = default;

    CommandBuffer(const Parameters &parameters);

    void reset();

    void begin();

    void end();

    struct ClearColorValue
    {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 0.0f;
    };

    struct RenderPassBeginInfo
    {
        RenderPass render_pass;
        FrameBuffer framebuffer;
        struct
        {
            int32_t x = 0;
            int32_t y = 0;
            uint32_t width = 0;
            uint32_t height = 0;
        } render_area = {};
        std::vector<ClearColorValue> clear_values = {};
    };

    void begin_render_pass(const RenderPassBeginInfo &info);

    void end_render_pass();

    void set_viewport(const Viewport &viewport);

    struct ScissorInfo
    {
        int32_t x = 0;
        int32_t y = 0;
        uint32_t width = 0;
        uint32_t height = 0;
    };

    void set_scissor(const ScissorInfo &viewport);

    void bind_pipeline(const Pipeline &pipeline);

    struct DrawInfo
    {
        uint32_t vertex_count = 0;
        uint32_t instance_count = 0;
        uint32_t first_vertex = 0;
        uint32_t first_instance = 0;
    };

    void draw(const DrawInfo &info);
};