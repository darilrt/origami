#include <iostream>

#include "origami/gfx.hpp"

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

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
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
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = info.engine_name.c_str(),
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };

    std::vector<const char *> extension_names = info.required_extensions;

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
        throw std::runtime_error("Failed to create Vulkan instance");
    }
}

void gfx::State::setup(const SetupInfo &info)
{
    create_instance(info);
    // setup_debug_messenger();
    // pick_physical_device();
    // create_logical_device();
    // create_swap_chain(window);
    // create_image_views();
    // create_command_pool();
    // create_command_buffer();
    // create_sync_objects();
}