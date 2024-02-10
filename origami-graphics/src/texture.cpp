#include <origami/core.hpp>
#include <origami/gfx.hpp>
#include <vulkan/vulkan.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "origami/graphics/texture.hpp"
#include "origami/graphics/graphics_system.hpp"

const std::string Texture::asset_type = "Graphics/Texture";

Texture *Texture::load_asset(const std::string &path, AssetManager &assets)
{
    int tex_width, tex_height, tex_channels;

    stbi_uc *pixels = stbi_load(path.c_str(), &tex_width, &tex_height, &tex_channels, STBI_rgb_alpha);

    if (!pixels)
    {
        throw std::runtime_error("Failed to load texture image " + path);
    }

    VkDeviceSize image_size = tex_width * tex_height * 4;

    Buffer staging_buffer = Buffer::create({
        .device = GraphicsSystem::vk_device,
        .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        .memory_properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        .size = image_size,
        .data = pixels,
    });

    stbi_image_free(pixels);

    std::cout << "Texture loaded: " << path << std::endl;

    auto *texture = new Texture();

    texture->image = new_unique<Image>();
    *texture->image = Image::create({
        .device = GraphicsSystem::vk_device,
        .width = (uint32_t)tex_width,
        .height = (uint32_t)tex_height,
        .depth = 1,
        .mip_levels = 1,
        .array_layers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .format = VK_FORMAT_R8G8B8A8_SRGB,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
        .sharing_mode = VK_SHARING_MODE_EXCLUSIVE,
        .memory_properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    });

    CommandBuffer cmd = GraphicsSystem::command_pool.allocate_command_buffer();

    cmd.begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    cmd.copy_buffer_to_image(staging_buffer.id, texture->image->id, (uint32_t)tex_width, (uint32_t)tex_height, 1);
    cmd.end();

    GraphicsSystem::vk_graphic_queue.submit({
        .command_buffers = {cmd.id},
    });
    GraphicsSystem::vk_graphic_queue.wait_idle();
    staging_buffer.destroy();
    cmd.destroy();

    return texture;
}