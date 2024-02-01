#include <vulkan/vulkan.h>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "origami/gfx/swap_chain.hpp"

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

SwapChainSupportDetails sc_query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR surface)
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

SwapChain SwapChain::create(const SwapChainInfo &info)
{
    SwapChain swap_chain;

    auto swap_chain_support = sc_query_swap_chain_support((VkPhysicalDevice)info.device.id, (VkSurfaceKHR)info.device.surface);

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
                info.extent.width));
        extent.height = std::max(
            swap_chain_support.capabilities.minImageExtent.height,
            std::min(
                swap_chain_support.capabilities.maxImageExtent.height,
                info.extent.height));
    }

    uint32_t image_count = swap_chain_support.capabilities.minImageCount + 1;

    if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount)
    {
        image_count = swap_chain_support.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR create_info = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = (VkSurfaceKHR)info.device.surface,
        .minImageCount = image_count,
        .imageFormat = surface_format.format,
        .imageColorSpace = surface_format.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
    };

    uint32_t queue_family_indices[] = {info.device.graphics_family.value(), info.device.present_family.value()};

    if (info.device.graphics_family.value() != info.device.present_family.value())
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

    VkResult result = vkCreateSwapchainKHR((VkDevice)info.device.device, &create_info, nullptr, (VkSwapchainKHR *)&swap_chain.id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::SwapChain::create: failed to create swap chain!");
    }

    uint32_t swap_chain_image_count;
    vkGetSwapchainImagesKHR((VkDevice)info.device.device, (VkSwapchainKHR)swap_chain.id, &swap_chain_image_count, nullptr);

    std::vector<VkImage> swap_chain_images(swap_chain_image_count);
    vkGetSwapchainImagesKHR((VkDevice)info.device.device, (VkSwapchainKHR)swap_chain.id, &swap_chain_image_count, swap_chain_images.data());

    swap_chain.images.resize(swap_chain_image_count);

    for (size_t i = 0; i < swap_chain_image_count; i++)
    {
        swap_chain.images[i].id = swap_chain_images[i];
        swap_chain.images[i].device = info.device.device;
        swap_chain.images[i].format = Image::Format::BGRA;
    }

    swap_chain.device = info.device.device;
    return swap_chain;
}

void SwapChain::destroy()
{
    vkDestroySwapchainKHR((VkDevice)id, (VkSwapchainKHR)id, nullptr);
}

uint32_t SwapChain::acquire_next_image(VulkanSemaphore semaphore)
{
    uint32_t image_index;
    vkAcquireNextImageKHR((VkDevice)device, (VkSwapchainKHR)id, UINT64_MAX, (VkSemaphore)semaphore.id, VK_NULL_HANDLE, &image_index);
    return image_index;
}