#include <origami/assets.hpp>
#include <toml++/toml.h>
#include <vulkan/vulkan.h>

#include "origami/graphics/graphics_system.hpp"
#include "origami/graphics/material.hpp"

const std::string Material::asset_type = "Graphics/Material";

Material *Material::load_asset(const std::string &path, AssetManager &asset_manager)
{
    toml::table data = toml::parse_file(path);

    if (!data.contains("properties"))
    {
        std::cerr << "Material file " << path << " does not contain a 'properties' table" << std::endl;
        return nullptr;
    }

    toml::table &properties = *data["properties"].as_table();

    if (!properties.contains("shader"))
    {
        std::cerr << "Material file " << path << " does not contain a 'shader' field" << std::endl;
        return nullptr;
    }

    std::string shader_uuid = properties["shader"].as_string()->get();
    Shared<Shader> shader = asset_manager.get<Shader>(shader_uuid);

    if (!shader)
    {
        std::cerr << "Material file " << path << " references a shader that does not exist" << std::endl;
        return nullptr;
    }

    Material *material = new Material();

    material->shader = shader;

    material->uniform_buffer = Buffer::create({
        .device = GraphicsSystem::vk_device,
        .usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        .memory_properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        .size = shader->uniform_size,
    });

    material->uniform_buffer.map_memory();

    return material;
}

void Material::set_uniform(const std::string &name, const void *data, size_t size)
{
    uint32_t offset = shader->offsets[name];

    memcpy(
        uniform_buffer.mapped + (shader->uniform_size - offset),
        data,
        size);
}