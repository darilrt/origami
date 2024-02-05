#include <origami/event.hpp>
#include <origami/window.hpp>
#include <origami/gfx.hpp>
#include <origami/assets.hpp>
#include <iostream>
#include <string>
#include <vulkan/vulkan.h>

#include "origami/graphics/primitives.hpp"
#include "origami/graphics/material.hpp"
#include "origami/graphics/render_pass.hpp"
#include "origami/graphics/graphics_system.hpp"
#include "origami/graphics/default_pass_material.hpp"
#include "origami/graphics/mesh.hpp"

const int MAX_FRAMES_IN_FLIGHT = 2;

VulkanDevice GraphicsSystem::vk_device;
RenderPass GraphicsSystem::render_pass;
VulkanQueue GraphicsSystem::vk_graphic_queue;
CommandPool GraphicsSystem::command_pool;
DescriptorPool GraphicsSystem::descriptor_pool;
uint32_t GraphicsSystem::frames_in_flight = MAX_FRAMES_IN_FLIGHT;

void GraphicsSystem::init(EngineState &state)
{
    this->state = &state;
    auto &window = state.get_resource<Window>();
    auto &es = state.get_resource<EventSystem>();

    viewport = {0, 0, window.get_size().x, window.get_size().y};

    es.regist<PreStart>(
        [&](EngineState &state, void *_)
        { _start(state); });

    es.regist<Render>(
        [&](EngineState &state, void *_)
        { _render(state); });

    es.regist<Stop>(
        [](EngineState &state, void *_) {});
}

Shared<GraphicEntity> GraphicsSystem::create_entity()
{
    auto entity = new_shared<GraphicEntity>();
    entities.push_back(entity);
    return entity;
}

Shared<RenderPassOld> GraphicsSystem::create_render_pass(int width, int height)
{
    auto render_pass = new_shared<RenderPassOld>(width, height);
    render_passes.push_back(render_pass);
    return render_pass;
}

GraphicsSystem::~GraphicsSystem()
{
    descriptor_pool.destroy();

    for (auto &framebuffer : swap_chain_framebuffers)
    {
        framebuffer.destroy();
    }

    for (auto &image_view : swap_chain_image_views)
    {
        image_view.destroy();
    }

    for (int i = 0; i < image_available_semaphores.size(); i++)
    {
        image_available_semaphores[i].destroy();
        render_finished_semaphores[i].destroy();
        in_flight_fences[i].destroy();
    }

    command_pool.destroy();
    swap_chain.destroy();
    vk_device.destroy();
    vk_instance.destroy();
}

void GraphicsSystem::_start(EngineState &state)
{
    Window &window = state.get_resource<Window>();
    std::vector<const char *> extensions = window.get_required_extensions();

    vk_instance = VulkanInstance::create({
        .app_info = {
            .app_name = "Test",
            .app_version = VK_MAKE_VERSION(1, 0, 0),
            .engine_name = "Origami",
            .engine_version = VK_MAKE_VERSION(1, 0, 0),
            .api_version = VK_API_VERSION_1_0,
        },
        .validation_layers = {},
        .required_extensions = extensions,
    });

    VkSurfaceKHR surface;
    window.create_surface_khr((VkInstance)vk_instance.id, &surface);

    vk_device = vk_instance.create_device(surface);
    vk_graphic_queue = VulkanQueue::create({
        .device = vk_device.device,
        .queue_family_index = vk_device.graphics_family.value(),
        .queue_index = 0,
    });
    vk_present_queue = VulkanQueue::create({
        .device = vk_device.device,
        .queue_family_index = vk_device.present_family.value(),
        .queue_index = 0,
    });

    swap_chain = SwapChain::create({
        .device = vk_device,
        .extent = {
            .width = static_cast<uint32_t>(window.get_size().x),
            .height = static_cast<uint32_t>(window.get_size().y),
        },
    });

    render_pass = RenderPass::create({
        .device = vk_device.device,
        .attachments = {
            {
                .id = 0,
                .format = (uint32_t)swap_chain.images[0].format,
            },
        },
    });

    for (auto &image : swap_chain.images)
    {
        swap_chain_image_views.push_back(ImageView::create({
            .device = (void *)vk_device.device,
            .image = image,
            .view_type = VK_IMAGE_VIEW_TYPE_2D,
            .components = {
                VK_COMPONENT_SWIZZLE_IDENTITY,
                VK_COMPONENT_SWIZZLE_IDENTITY,
                VK_COMPONENT_SWIZZLE_IDENTITY,
                VK_COMPONENT_SWIZZLE_IDENTITY,
            },
            .subresource_range = {
                .aspect_mask = VK_IMAGE_ASPECT_COLOR_BIT,
                .base_mip_level = 0,
                .level_count = 1,
                .base_array_layer = 0,
                .layer_count = 1,
            },
        }));

        swap_chain_framebuffers.push_back(FrameBuffer::create({
            .device = vk_device.device,
            .render_pass = render_pass,
            .width = static_cast<uint32_t>(window.get_size().x),
            .height = static_cast<uint32_t>(window.get_size().y),
            .layers = 1,
            .attachments = {swap_chain_image_views.back()},
        }));
    }

    command_pool = CommandPool::create({
        .device = vk_device.device,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queue_family_index = vk_device.graphics_family.value(),
    });

    for (size_t i = 0; i < swap_chain.images.size(); i++)
    {
        command_buffers.push_back(command_pool.allocate_command_buffer());
    }

    image_available_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    render_finished_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        image_available_semaphores[i] = VulkanSemaphore::create({
            .device = vk_device.device,
        });
        render_finished_semaphores[i] = VulkanSemaphore::create({
            .device = vk_device.device,
        });
        in_flight_fences[i] = VulkanFence::create({
            .device = vk_device.device,
            .flags = VK_FENCE_CREATE_SIGNALED_BIT,
        });
    }

    descriptor_pool = DescriptorPool::create({
        .device = vk_device.device,
        .descriptor_count = MAX_FRAMES_IN_FLIGHT,
        .max_sets = MAX_FRAMES_IN_FLIGHT,
    });

    static auto &assets = state.get_resource<AssetManager>();
    static Shared<Material> mat = assets.get<Material>("1a68269c-821e-916d-f76f-e005015ba175");
}

void GraphicsSystem::_render(EngineState &state)
{
    static auto &wm = state.get_resource<Window>();
    static auto &assets = state.get_resource<AssetManager>();
    static Shared<Material> mat = assets.get<Material>("1a68269c-821e-916d-f76f-e005015ba175");
    static Mesh *mesh = nullptr;

    if (mesh == nullptr)
    {
        mesh = new Mesh({
            {{0.0f, -0.5f, 0.0f}, {1.0, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        });
    }

    VulkanFence fence = in_flight_fences[current_frame];
    fence.wait();
    uint32_t image_index = swap_chain.acquire_next_image(image_available_semaphores[current_frame]);
    fence.reset();
    FrameBuffer fb = swap_chain_framebuffers[image_index];
    CommandBuffer cmd = command_buffers[current_frame];

    static float timer = 0;
    timer += 0.002f;
    mat->set_uniform("time", timer);
    mat->set_uniform("color", 0.5f);

    // ((float *)mat->uniform_buffer.mapped)[3] = 0.5f;

    cmd.reset();
    cmd.begin();

    cmd.begin_render_pass({
        .render_pass = render_pass,
        .framebuffer = fb,
        .render_area = {
            .x = 0,
            .y = 0,
            .width = static_cast<uint32_t>(wm.get_size().x),
            .height = static_cast<uint32_t>(wm.get_size().y),
        },
        .clear_values = {{0, 0, 0, 0}},
    });

    cmd.bind_pipeline(mat->shader->pipeline);

    mat->shader->descriptor_set[current_frame].update({
        {
            .buffer = mat->uniform_buffer.id,
            .binding = 0,
            .array_element = 0,
        },
    });

    cmd.bind_descriptor_sets({
        .pipeline_bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .pipeline_layout = mat->shader->pipeline.layout,
        .first_set = 0,
        .descriptor_sets = {mat->shader->descriptor_set[current_frame].id},
    });

    cmd.bind_vertex_buffers({mesh->buffer.id}, {0ULL});

    cmd.set_viewport({
        .x = 0.0f,
        .y = 0.0f,
        .width = static_cast<float>(wm.get_size().x),
        .height = static_cast<float>(wm.get_size().y),
    });

    cmd.set_scissor({
        .x = 0,
        .y = 0,
        .width = static_cast<uint32_t>(wm.get_size().x),
        .height = static_cast<uint32_t>(wm.get_size().y),
    });

    cmd.draw({
        .vertex_count = mesh->vertices_count,
        .instance_count = 1,
        .first_vertex = 0,
        .first_instance = 0,
    });

    cmd.end_render_pass();

    cmd.end();

    vk_graphic_queue.submit({
        .command_buffers = {cmd.id},
        .wait_semaphores = {image_available_semaphores[current_frame]},
        .wait_stages = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT},
        .signal_semaphores = {render_finished_semaphores[current_frame]},
        .fence = fence,
    });

    vk_present_queue.present({
        .wait_semaphores = {render_finished_semaphores[current_frame]},
        .image_indices = {image_index},
        .swap_chains = {swap_chain},
    });

    current_frame = (current_frame + 1) % 2;
}