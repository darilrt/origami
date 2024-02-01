#include <iostream>
#include <string>
#include <map>
#include <set>

#include "origami/gfx.hpp"

const int MAX_FRAMES_IN_FLIGHT = 2;

void gfx::State::create_sync_objects()
{
    image_available_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    render_finished_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphore_info{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    };

    VkFenceCreateInfo fence_info{
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT,
    };

    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        bool result = vkCreateSemaphore((VkDevice)vk_device.device, &semaphore_info, nullptr, &image_available_semaphores[i]) != VK_SUCCESS;
        result |= vkCreateSemaphore((VkDevice)vk_device.device, &semaphore_info, nullptr, &render_finished_semaphores[i]) != VK_SUCCESS;
        result |= vkCreateFence((VkDevice)vk_device.device, &fence_info, nullptr, &in_flight_fences[i]) != VK_SUCCESS;

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("gfx::State::create_sync_objects: failed to create synchronization objects");
        }
    }
}

void gfx::State::recreate_swap_chain()
{
    vkDeviceWaitIdle((VkDevice)vk_device.device);

    // cleanup_swap_chain();

    // create_image_views();
    // create_render_pass();
    // create_framebuffers();
}

gfx::State::~State()
{
    // vkDeviceWaitIdle((VkDevice)vk_device.device);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore((VkDevice)vk_device.device, render_finished_semaphores[i], nullptr);
        vkDestroySemaphore((VkDevice)vk_device.device, image_available_semaphores[i], nullptr);
        vkDestroyFence((VkDevice)vk_device.device, in_flight_fences[i], nullptr);
    }

    command_pool.destroy();

    vk_device.destroy();
    instance.destroy();
}

void gfx::State::setup(const SetupInfo &info)
{
    get_extent = info.get_extent;

    instance = VulkanInstance::create({
        .app_info = {
            .app_name = info.app_name,
            .app_version = info.app_version,
            .engine_name = info.engine_name,
            .engine_version = info.engine_version,
            .api_version = info.api_version,
        },
        .validation_layers = info.validation_layers,
        .required_extensions = info.required_extensions,
    });

    if (info.create_surface)
    {
        info.create_surface();
    }
    else
    {
        throw std::runtime_error("gfx::State::setup: no create_surface function provided");
    }

    vk_device = instance.create_device(surface);

    VkExtent2D extent = get_extent();

    swap_chain = SwapChain::create({
        .device = vk_device,
        .extent = {
            .width = extent.width,
            .height = extent.height,
        },
    });

    swap_chain_images = swap_chain.images;

    for (const auto &image : swap_chain_images)
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
    }

    render_pass = RenderPass({
        .device = (void *)vk_device.device,
        .attachments = {
            {
                .id = 0,
                .format = (uint32_t)swap_chain_images[0].format,
            },
        },
    });

    for (auto image_view : swap_chain_image_views)
    {
        swap_chain_framebuffers.push_back(FrameBuffer({
            .device = (void *)vk_device.device,
            .render_pass = render_pass,
            .width = extent.width,
            .height = extent.height,
            .layers = 1,
            .attachments = {
                image_view,
            },
        }));
    }

    command_pool = CommandPool({
        .device = (void *)vk_device.device,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queue_family_index = vk_device.graphics_family.value(),
    });

    command_buffers.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < command_buffers.size(); i++)
    {
        command_buffers[i] = command_pool.allocate_command_buffer();
    }

    create_sync_objects();
}

void gfx::State::wait_for_render()
{
    vkWaitForFences((VkDevice)vk_device.device, 1, &in_flight_fences[current_frame], VK_TRUE, UINT64_MAX);

    VkResult result = vkAcquireNextImageKHR((VkDevice)vk_device.device, (VkSwapchainKHR)swap_chain.id, UINT64_MAX, image_available_semaphores[current_frame], VK_NULL_HANDLE, &image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        recreate_swap_chain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("Failed to acquire swap chain image");
    }

    vkResetFences((VkDevice)vk_device.device, 1, &in_flight_fences[current_frame]);
}

void gfx::State::submit(const std::vector<CommandBuffer> &command_buffers)
{
    VkSemaphore wait_semaphores[] = {image_available_semaphores[current_frame]};
    VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    VkSemaphore signal_semaphores[] = {render_finished_semaphores[current_frame]};

    VkSubmitInfo submit_info{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = wait_semaphores,
        .pWaitDstStageMask = wait_stages,
        .commandBufferCount = static_cast<uint32_t>(command_buffers.size()),
        .pCommandBuffers = (VkCommandBuffer *)command_buffers.data(),
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = signal_semaphores,
    };

    VkResult submit_result = vkQueueSubmit(
        (VkQueue)vk_device.graphics_queue,
        1, &submit_info, in_flight_fences[current_frame]);

    if (submit_result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to submit draw command buffer");
    }
}

void gfx::State::draw_frame()
{
    VkSemaphore signal_semaphores[] = {render_finished_semaphores[current_frame]};

    VkSwapchainKHR swap_chains[] = {(VkSwapchainKHR)swap_chain.id};

    VkPresentInfoKHR present_info{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = signal_semaphores,
        .swapchainCount = 1,
        .pSwapchains = &swap_chains[0],
        .pImageIndices = &image_index,
        .pResults = nullptr,
    };

    VkResult result = vkQueuePresentKHR(
        (VkQueue)vk_device.graphics_queue,
        &present_info);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        recreate_swap_chain();
    }
    else if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to present swap chain image");
    }

    current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}
