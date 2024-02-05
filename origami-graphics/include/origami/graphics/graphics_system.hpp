#pragma once

#include <origami/core.hpp>
#include <origami/gfx.hpp>

#include "origami/graphics/entity.hpp"
#include "origami/graphics/render_pass.hpp"

class GraphicsSystem : public Resource
{
public:
    ~GraphicsSystem();

    void init(EngineState &state);

    void set_viewport(Vec4 size) { this->viewport = size; }

    void set_view(Mat4 view) { this->view = view; }

    void set_projection(Mat4 projection) { this->projection = projection; }

    void set_render_pass(Shared<RenderPassOld> render_pass) { this->current_render_pass = render_pass; }

    Shared<GraphicEntity> create_entity();

    Shared<RenderPassOld> create_render_pass(int width, int height);

    std::vector<Shared<GraphicEntity>> entities;
    std::vector<Shared<RenderPassOld>> render_passes;
    Shared<RenderPassOld> current_render_pass = nullptr;
    EngineState *state;
    Vec4 viewport;
    Mat4 view;
    Mat4 projection;

    static uint32_t frames_in_flight;
    VulkanInstance vk_instance;
    static VulkanDevice vk_device;
    static VulkanQueue vk_graphic_queue;
    VulkanQueue vk_present_queue;
    SwapChain swap_chain;
    std::vector<ImageView> swap_chain_image_views;
    std::vector<FrameBuffer> swap_chain_framebuffers;
    static RenderPass render_pass;
    static CommandPool command_pool;
    std::vector<CommandBuffer> command_buffers;
    int current_frame = 0;
    std::vector<VulkanSemaphore> image_available_semaphores;
    std::vector<VulkanSemaphore> render_finished_semaphores;
    std::vector<VulkanFence> in_flight_fences;
    static DescriptorPool descriptor_pool;
    std::vector<DescriptorSet> descriptor_sets;

    void _start(EngineState &state);

    void _render(EngineState &state);

    void _render_entity(GraphicEntity &entity);
};