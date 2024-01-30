#include <vulkan/vulkan.h>
#include <iostream>

#include "origami/gfx/vk_instance.hpp"

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

VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
    void *user_data)
{
    std::cerr << "Validation layer: " << callback_data->pMessage << std::endl;

    return VK_FALSE;
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

VulkanInstance VulkanInstance::create(const InstanceInfo &info)
{
    VulkanInstance instance;

    std::vector<const char *> extensions = info.required_extensions;

#ifdef VULKAN_DEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    std::vector<const char *> validation_layers = info.validation_layers;

#ifdef VULKAN_DEBUG
    validation_layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

    VkApplicationInfo app_info = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .pApplicationName = info.app_info.app_name.c_str(),
        .applicationVersion = info.app_info.app_version,
        .pEngineName = info.app_info.engine_name.c_str(),
        .engineVersion = info.app_info.engine_version,
        .apiVersion = info.app_info.api_version,
    };

    VkInstanceCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .pApplicationInfo = &app_info,
        .enabledLayerCount = static_cast<uint32_t>(validation_layers.size()),
        .ppEnabledLayerNames = validation_layers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data(),
    };

#ifdef VULKAN_DEBUG
    VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
    populate_debug_messenger_create_info(debug_create_info, debug_callback);
    create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debug_create_info;
#endif

    if (vkCreateInstance(&create_info, nullptr, (VkInstance *)&instance.id) != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::VulkanInstance::create: failed to create instance!");
    }

#ifdef VULKAN_DEBUG
    debug_create_info = {};
    populate_debug_messenger_create_info(debug_create_info, debug_callback);
    VkDebugUtilsMessengerEXT debug_messenger;

    if (create_debug_utils_messenger_EXT((VkInstance)instance.id, &debug_create_info, nullptr, &debug_messenger) != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::State::setup_debug_messenger: failed to set up debug messenger");
    }
#endif

    return instance;
}

void VulkanInstance::destroy()
{
#ifdef VULKAN_DEBUG
    destroy_debug_utils_messenger_EXT((VkInstance)id, (VkDebugUtilsMessengerEXT)debug_messenger, nullptr);
#endif

    vkDestroyInstance((VkInstance)id, nullptr);
}

VulkanDevice VulkanInstance::create_device(void *surface)
{
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices((VkInstance)id, &device_count, nullptr);

    if (device_count == 0)
    {
        throw std::runtime_error("gfx::VulkanInstance::get_best_device: failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices((VkInstance)id, &device_count, devices.data());

    for (const auto &device : devices)
    {
        VkPhysicalDeviceProperties device_properties;
        vkGetPhysicalDeviceProperties(device, &device_properties);

        if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            return VulkanDevice::from_id({
                .id = device,
                .surface = surface,
                .extensions = {
                    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                },
            });
        }
    }

    return VulkanDevice::from_id({
        .id = devices[0],
        .surface = surface,
        .extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        },
    });
}