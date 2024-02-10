#pragma once

#include <vector>

#include "origami/gfx/pipeline.hpp"
#include "origami/gfx/framebuffer.hpp"
#include "origami/gfx/render_pass.hpp"
#include "origami/gfx/type.hpp"

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
    vkid_t id = 0;
    vkid_t device = 0;
    vkid_t command_pool = 0;

    struct Parameters
    {
        vkid_t device = 0;
        vkid_t command_pool = 0;
        uint32_t level = 0;
    };

    CommandBuffer() = default;

    CommandBuffer(const Parameters &parameters);

    void destroy();

    void reset();

    void begin(uint32_t flags = 1);

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

    struct DescriptorSetInfo
    {
        uint32_t pipeline_bind_point = 0;
        vkid_t pipeline_layout = 0;
        uint32_t first_set = 0;
        std::vector<vkid_t> descriptor_sets = {};
    };

    void bind_descriptor_sets(const DescriptorSetInfo &info);

    struct DrawInfo
    {
        uint32_t vertex_count = 0;
        uint32_t instance_count = 0;
        uint32_t first_vertex = 0;
        uint32_t first_instance = 0;
    };

    void draw(const DrawInfo &info);

    void bind_vertex_buffers(const std::vector<void *> &buffers, const std::vector<uint64_t> &offsets);

    void copy_buffer(vkid_t src, vkid_t dst, uint64_t size);

    void copy_buffer_to_image(vkid_t src, vkid_t dst, uint32_t width, uint32_t height, uint32_t depth);
};