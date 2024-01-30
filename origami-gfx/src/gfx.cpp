#include <iostream>
#include <string>
#include <map>
#include <set>

#include "origami/gfx.hpp"

const int MAX_FRAMES_IN_FLIGHT = 2;

VkResult create_debug_utils_messenger_EXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *create_info, const VkAllocationCallbacks *allocator, VkDebugUtilsMessengerEXT *debug_messenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func != nullptr)
    {
        return func(instance, create_info, allocator, debug_messenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    return VK_SUCCESS;
}

VkResult destroy_debug_utils_messenger_EXT(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks *allocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if (func != nullptr)
    {
        func(instance, debug_messenger, allocator);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    return VK_SUCCESS;
}

void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &create_info, PFN_vkDebugUtilsMessengerCallbackEXT callback)
{
    create_info = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = callback,
        .pUserData = nullptr,
    };
}

VKAPI_ATTR VkBool32 VKAPI_CALL gfx::State::debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
    void *user_data)
{
    std::cerr << "Validation layer: " << callback_data->pMessage << std::endl;

    return VK_FALSE;
}

void gfx::State::create_instance(const SetupInfo &info)
{
    VkApplicationInfo app_info = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = info.app_name.c_str(),
        .applicationVersion = info.api_version,
        .pEngineName = info.engine_name.c_str(),
        .engineVersion = info.engine_version,
        .apiVersion = info.api_version,
    };

    std::vector<const char *> extension_names = info.required_extensions;

    if (info.enable_validation_layers)
    {
        extension_names.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    VkInstanceCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .pApplicationInfo = &app_info,
        .enabledLayerCount = 0,
        .enabledExtensionCount = static_cast<uint32_t>(extension_names.size()),
        .ppEnabledExtensionNames = extension_names.data(),
    };

    if (info.enable_validation_layers)
    {
        create_info.enabledLayerCount = static_cast<uint32_t>(info.validation_layers.size());
        create_info.ppEnabledLayerNames = info.validation_layers.data();

        VkDebugUtilsMessengerCreateInfoEXT debug_messenger_create_info = {};
        populate_debug_messenger_create_info(debug_messenger_create_info, debug_callback);
        create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debug_messenger_create_info;
    }

    VkResult result = vkCreateInstance(&create_info, nullptr, &instance);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::State::create_instance: failed to create instance");
    }
}

void gfx::State::setup_debug_messenger(bool enable_validation_layers)
{
    if (!enable_validation_layers)
    {
        return;
    }

    VkDebugUtilsMessengerCreateInfoEXT create_info = {};
    populate_debug_messenger_create_info(create_info, debug_callback);

    if (create_debug_utils_messenger_EXT(instance, &create_info, nullptr, &debug_messenger) != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::State::setup_debug_messenger: failed to set up debug messenger");
    }
}

void gfx::State::pick_physical_device()
{
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance, &device_count, nullptr);
    if (device_count == 0)
    {
        throw std::runtime_error("Failed to find GPUs with Vulkan support");
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto &device : devices)
    {
        int score = rate_device_suitable(device);

        candidates.insert(std::make_pair(score, device));
    }

    if (candidates.rbegin()->first > 0)
    {
        physical_device = candidates.rbegin()->second;
    }
    else
    {
        throw std::runtime_error("gfx::State::pick_physical_device: failed to find a suitable GPU");
    }
}

int gfx::State::rate_device_suitable(VkPhysicalDevice device)
{
    // Query for basic device properties
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    // Query for optional device features like texture compression, 64 bit floats and multi viewport rendering
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    int score = 0;

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        score += 1000;
    }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader)
    {
        return 0;
    }

    uint32_t extension_count;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);

    std::vector<VkExtensionProperties> available_extensions(extension_count);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());

    std::set<std::string> required_extensions(device_extensions.begin(), device_extensions.end());

    for (const auto &extension : available_extensions)
    {
        required_extensions.erase(extension.extensionName);
    }

    // Check if all required extensions are available
    if (!required_extensions.empty())
    {
        return 0;
    }

    bool swap_chain_adequate = false;
    if (required_extensions.empty())
    {
        SwapChainSupportDetails swap_chain_support = query_swap_chain_support(device);
        swap_chain_adequate = !swap_chain_support.formats.empty() && !swap_chain_support.present_modes.empty();
    }

    if (!swap_chain_adequate)
    {
        return 0;
    }

    return score;
}

gfx::SwapChainSupportDetails gfx::State::query_swap_chain_support(VkPhysicalDevice device)
{
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t format_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);

    if (format_count != 0)
    {
        details.formats.resize(format_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, details.formats.data());
    }

    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);

    if (present_mode_count != 0)
    {
        details.present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, details.present_modes.data());
    }

    return details;
}

void gfx::State::create_logical_device(const SetupInfo &info)
{
    QueueFamilyIndices indices = find_queue_families(physical_device);

    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    std::set<uint32_t> unique_queue_families = {indices.graphics_family.value(), indices.present_family.value()};

    float queue_priority = 1.0f;
    for (uint32_t queue_family : unique_queue_families)
    {
        queue_create_infos.push_back(VkDeviceQueueCreateInfo{
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = queue_family,
            .queueCount = 1,
            .pQueuePriorities = &queue_priority,
        });
    }

    VkPhysicalDeviceFeatures device_features = {};

    VkDeviceCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size()),
        .pQueueCreateInfos = queue_create_infos.data(),
        .enabledLayerCount = 0,
        .enabledExtensionCount = static_cast<uint32_t>(device_extensions.size()),
        .ppEnabledExtensionNames = device_extensions.data(),
        .pEnabledFeatures = &device_features,
    };

    VkResult result = vkCreateDevice(physical_device, &create_info, nullptr, &device);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create logical device");
    }

    vkGetDeviceQueue(device, indices.graphics_family.value(), 0, &graphics_queue);
}

gfx::QueueFamilyIndices gfx::State::find_queue_families(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

    int i = 0;
    for (const auto &queue_family : queue_families)
    {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphics_family = i;
        }

        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);

        if (present_support)
        {
            indices.present_family = i;
        }

        if (indices.is_complete())
        {
            break;
        }

        i++;
    }

    return indices;
}

void gfx::State::create_swap_chain(const VkExtent2D &window_extent)
{
    SwapChainSupportDetails swap_chain_support = query_swap_chain_support(physical_device);

    VkSurfaceFormatKHR surface_format = swap_chain_support.formats[0];

    for (const auto &available_format : swap_chain_support.formats)
    {
        if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB && available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            surface_format = available_format;
            break;
        }
    }

    VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;

    for (const auto &available_present_mode : swap_chain_support.present_modes)
    {
        if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            present_mode = available_present_mode;
            break;
        }
        else if (available_present_mode == VK_PRESENT_MODE_IMMEDIATE_KHR)
        {
            present_mode = available_present_mode;
        }
    }

    VkExtent2D extent;

    if (swap_chain_support.capabilities.currentExtent.width != UINT32_MAX)
    {
        extent = swap_chain_support.capabilities.currentExtent;
    }
    else
    {
        extent.width = std::max(
            swap_chain_support.capabilities.minImageExtent.width,
            std::min(
                swap_chain_support.capabilities.maxImageExtent.width,
                window_extent.width));
        extent.height = std::max(
            swap_chain_support.capabilities.minImageExtent.height,
            std::min(
                swap_chain_support.capabilities.maxImageExtent.height,
                window_extent.height));
    }

    uint32_t image_count = swap_chain_support.capabilities.minImageCount + 1;

    if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount)
    {
        image_count = swap_chain_support.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR create_info = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = surface,
        .minImageCount = image_count,
        .imageFormat = surface_format.format,
        .imageColorSpace = surface_format.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
    };

    QueueFamilyIndices indices = find_queue_families(physical_device);
    uint32_t queue_family_indices[] = {indices.graphics_family.value(), indices.present_family.value()};

    if (indices.graphics_family != indices.present_family)
    {
        create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        create_info.queueFamilyIndexCount = 2;
        create_info.pQueueFamilyIndices = queue_family_indices;
    }
    else
    {
        create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        create_info.queueFamilyIndexCount = 0;
        create_info.pQueueFamilyIndices = nullptr;
    }

    create_info.preTransform = swap_chain_support.capabilities.currentTransform;
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = present_mode;
    create_info.clipped = VK_TRUE;
    create_info.oldSwapchain = VK_NULL_HANDLE;

    VkResult result = vkCreateSwapchainKHR(device, &create_info, nullptr, &swap_chain);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::State::create_swap_chain: failed to create swap chain");
    }

    vkGetSwapchainImagesKHR(device, swap_chain, &image_count, nullptr);
    std::vector<VkImage> chain_images(image_count);
    swap_chain_images.resize(image_count);
    vkGetSwapchainImagesKHR(device, swap_chain, &image_count, chain_images.data());

    for (int i = 0; i < image_count; i++)
    {
        swap_chain_images[i].id = chain_images[i];
    }

    swap_chain_image_format = surface_format.format;
    swap_chain_extent = extent;
}

void gfx::State::cleanup_swap_chain()
{
    vkDestroySwapchainKHR(device, swap_chain, nullptr);
}

void gfx::State::create_command_pool()
{
    QueueFamilyIndices queue_family_indices = find_queue_families(physical_device);

    VkCommandPoolCreateInfo pool_info = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = queue_family_indices.graphics_family.value(),
    };

    VkResult result = vkCreateCommandPool(device, &pool_info, nullptr, &command_pool);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::State::create_command_pool: failed to create command pool");
    }
}

void gfx::State::create_command_buffer()
{
    command_buffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo alloc_info{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = command_pool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = static_cast<uint32_t>(command_buffers.size()),
    };

    VkResult result = vkAllocateCommandBuffers(device, &alloc_info, command_buffers.data());

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::State::create_command_buffer: failed to allocate command buffers");
    }
}

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
        bool result = vkCreateSemaphore(device, &semaphore_info, nullptr, &image_available_semaphores[i]) != VK_SUCCESS;
        result |= vkCreateSemaphore(device, &semaphore_info, nullptr, &render_finished_semaphores[i]) != VK_SUCCESS;
        result |= vkCreateFence(device, &fence_info, nullptr, &in_flight_fences[i]) != VK_SUCCESS;

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("gfx::State::create_sync_objects: failed to create synchronization objects");
        }
    }
}

void gfx::State::create_image_views()
{
    for (const auto &image : swap_chain_images)
    {
        swap_chain_image_views.push_back(ImageView({
            .device = (void *)device,
            .image = image,
            .view_type = VK_IMAGE_VIEW_TYPE_2D,
            .format = static_cast<uint32_t>(swap_chain_image_format),
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
}

void gfx::State::create_render_pass()
{
    render_pass = RenderPass({
        .device = (void *)device,
        .attachments = {
            {
                .id = 0,
                .format = static_cast<uint32_t>(swap_chain_image_format),
            },
        },
    });
}

void gfx::State::create_framebuffers()
{
    for (auto image_view : swap_chain_image_views)
    {
        swap_chain_framebuffers.push_back(FrameBuffer({
            .device = (void *)device,
            .render_pass = render_pass,
            .width = swap_chain_extent.width,
            .height = swap_chain_extent.height,
            .layers = 1,
            .attachments = {
                image_view,
            },
        }));
    }
}

void gfx::State::recreate_swap_chain()
{
    vkDeviceWaitIdle(device);

    cleanup_swap_chain();

    create_swap_chain(get_extent());
    create_image_views();
    create_render_pass();
    create_framebuffers();
}

gfx::State::~State()
{
    vkDeviceWaitIdle(device);

    cleanup_swap_chain();

    if (enable_validation_layers)
    {
        destroy_debug_utils_messenger_EXT(instance, debug_messenger, nullptr);
    }

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore(device, render_finished_semaphores[i], nullptr);
        vkDestroySemaphore(device, image_available_semaphores[i], nullptr);
        vkDestroyFence(device, in_flight_fences[i], nullptr);
    }

    vkDestroyCommandPool(device, command_pool, nullptr);

    // vkDestroyDevice(device, nullptr);
    // vkDestroySurfaceKHR(instance, surface, nullptr);
    // vkDestroyInstance(instance, nullptr);
}

void gfx::State::setup(const SetupInfo &info)
{
    get_extent = info.get_extent;
    enable_validation_layers = info.enable_validation_layers;

    create_instance(info);
    setup_debug_messenger(info.enable_validation_layers);

    if (info.create_surface)
    {
        info.create_surface();
    }
    else
    {
        throw std::runtime_error("gfx::State::setup: no create_surface function provided");
    }

    pick_physical_device();
    create_logical_device(info);

    create_swap_chain(info.get_extent());
    create_image_views();
    create_render_pass();
    create_framebuffers();

    create_command_pool();
    create_command_buffer();
    create_sync_objects();
}

void gfx::State::wait_for_render()
{
    vkWaitForFences(device, 1, &in_flight_fences[current_frame], VK_TRUE, UINT64_MAX);

    VkResult result = vkAcquireNextImageKHR(device, swap_chain, UINT64_MAX, image_available_semaphores[current_frame], VK_NULL_HANDLE, &image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        recreate_swap_chain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("Failed to acquire swap chain image");
    }

    vkResetFences(device, 1, &in_flight_fences[current_frame]);
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

    VkResult submit_result = vkQueueSubmit(graphics_queue, 1, &submit_info, in_flight_fences[current_frame]);

    if (submit_result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to submit draw command buffer");
    }
}

void gfx::State::draw_frame()
{
    VkSemaphore signal_semaphores[] = {render_finished_semaphores[current_frame]};

    VkSwapchainKHR swap_chains[] = {swap_chain};

    VkPresentInfoKHR present_info{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = signal_semaphores,
        .swapchainCount = 1,
        .pSwapchains = &swap_chains[0],
        .pImageIndices = &current_frame,
        .pResults = nullptr,
    };

    VkResult result = vkQueuePresentKHR(graphics_queue, &present_info);

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

CommandPool gfx::State::allocate_command_pool()
{
    return CommandPool({
        .device = (void *)device,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queue_family_index = find_queue_families(physical_device).graphics_family.value(),
    });
}