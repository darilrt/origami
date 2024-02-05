#include <iostream>
#include <filesystem>
#include <fstream>
#include <origami/assets.hpp>
#include <origami/gfx.hpp>
#include <vulkan/vulkan.h>
#include <toml++/toml.hpp>

#include "origami/graphics/graphics_system.hpp"
#include "origami/graphics/shader.hpp"

std::string Shader::asset_type = "Graphics/Shader";

std::unordered_map<std::string, std::pair<VkFormat, int>> format_map = {
    {"int", {VK_FORMAT_R32_SINT, 4}},
    {"ivec2", {VK_FORMAT_R32G32_SINT, 8}},
    {"ivec3", {VK_FORMAT_R32G32B32_SINT, 12}},
    {"ivec4", {VK_FORMAT_R32G32B32A32_SINT, 16}},
    {"uint", {VK_FORMAT_R32_UINT, 4}},
    {"uvec2", {VK_FORMAT_R32G32_UINT, 8}},
    {"uvec3", {VK_FORMAT_R32G32B32_UINT, 12}},
    {"uvec4", {VK_FORMAT_R32G32B32A32_UINT, 16}},
    {"float", {VK_FORMAT_R32_SFLOAT, 4}},
    {"vec2", {VK_FORMAT_R32G32_SFLOAT, 8}},
    {"vec3", {VK_FORMAT_R32G32B32_SFLOAT, 12}},
    {"vec4", {VK_FORMAT_R32G32B32A32_SFLOAT, 16}},
    {"double", {VK_FORMAT_R64_SFLOAT, 8}},
    {"dvec2", {VK_FORMAT_R64G64_SFLOAT, 16}},
    {"dvec3", {VK_FORMAT_R64G64B64_SFLOAT, 24}},
    {"dvec4", {VK_FORMAT_R64G64B64A64_SFLOAT, 32}},
    {"mat2", {VK_FORMAT_R32G32_SFLOAT, 16}},
    {"mat3", {VK_FORMAT_R32G32B32_SFLOAT, 36}},
    {"mat4", {VK_FORMAT_R32G32B32A32_SFLOAT, 64}},
    {"mat2x3", {VK_FORMAT_R32G32B32_SFLOAT, 24}},
    {"mat2x4", {VK_FORMAT_R32G32B32A32_SFLOAT, 32}},
    {"mat3x2", {VK_FORMAT_R32G32B32_SFLOAT, 24}},
    {"mat3x4", {VK_FORMAT_R32G32B32A32_SFLOAT, 48}},
    {"mat4x2", {VK_FORMAT_R32G32B32_SFLOAT, 32}},
    {"mat4x3", {VK_FORMAT_R32G32B32A32_SFLOAT, 48}},
};

Shader *Shader::load_asset(const std::string &path, AssetManager &asset_manager)
{
    toml::table data = toml::parse_file(path);

    if (!data.contains("modules"))
    {
        std::cerr << "Modules missing for shader: " << path << std::endl;
        return nullptr;
    }

    toml::table &modules = *data["modules"].as_table();

    if (!modules.contains("vertex") || !modules.contains("fragment"))
    {
        std::cerr << "Vertex or fragment missing for shader: " << path << std::endl;
        return nullptr;
    }

    std::string vertex_uuid = modules["vertex"].as_string()->get();
    std::string fragment_uuid = modules["fragment"].as_string()->get();

    if (!asset_manager.contains(vertex_uuid) || !asset_manager.contains(fragment_uuid))
    {
        std::cerr << "Vertex or fragment missing reference for shader: " << path << std::endl;
        return nullptr;
    }

    ShaderModule vertex_module = ShaderModule::create({
        .device = GraphicsSystem::vk_device.device,
        .file_path = asset_manager.assets[vertex_uuid].first + ".spv",
    });

    ShaderModule fragment_module = ShaderModule::create({
        .device = GraphicsSystem::vk_device.device,
        .file_path = asset_manager.assets[fragment_uuid].first + ".spv",
    });

    std::vector<BindingDescription> binding_descriptions;
    std::vector<AttributeDescription> attribute_descriptions;

    if (data.contains("bindings"))
    {
        toml::array &bindings = *data["bindings"].as_array();

        for (const auto &binding : bindings)
        {
            const toml::table &bind = *binding.as_table();

            BindingDescription desc = {
                .binding = static_cast<uint32_t>(bind["binding"].as_integer()->get()),
                .stride = 0,
                .input_rate = bind["input_rate"].as_string()->get() == "vertex" ? VK_VERTEX_INPUT_RATE_VERTEX : VK_VERTEX_INPUT_RATE_INSTANCE,
            };

            binding_descriptions.push_back(desc);
        }
    }

    if (data.contains("attributes") && binding_descriptions.size() > 0)
    {
        toml::table &attributes = *data["attributes"].as_table();

        for (const auto &attribute : attributes)
        {
            const toml::table &attr = *attribute.second.as_table();

            uint32_t binding = (uint32_t)attr["binding"].as_integer()->get();
            auto format = format_map[attr["format"].as_string()->get()];

            binding_descriptions[binding].stride += format.second;

            AttributeDescription desc = {
                .location = (uint32_t)attr["location"].as_integer()->get(),
                .binding = binding,
                .format = format.first,
                .offset = (uint32_t)attr["offset"].as_integer()->get(),
            };

            attribute_descriptions.push_back(desc);
        }
    }

    std::vector<DescriptorSetLayoutBinding> descriptor_set_layout_bindings;

    Shader *shader = new Shader();

    if (data.contains("uniforms"))
    {
        toml::table &uniforms = *data["uniforms"].as_table();

        uint32_t total_size = 0;
        for (const auto &uniform : uniforms)
        {
            std::string name = std::string(uniform.first.str());
            uint32_t size = format_map[uniform.second.as_string()->get()].second;

            total_size += size;
            shader->offsets[name] = total_size;
        }

        descriptor_set_layout_bindings.push_back({
            .binding = 0,
            .descriptor_type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptor_count = 1,
            .stage_flags = VK_SHADER_STAGE_ALL_GRAPHICS,
            .immutable_samplers = nullptr,
        });

        shader->uniform_size = total_size;
    }

    shader->pipeline = Pipeline::create({
        .device = GraphicsSystem::vk_device.device,
        .vs_module = vertex_module,
        .fs_module = fragment_module,
        .render_pass = GraphicsSystem::render_pass,
        .binding_descriptions = binding_descriptions,
        .attribute_descriptions = attribute_descriptions,
        .descriptor_set_layout_bindings = descriptor_set_layout_bindings,
    });

    shader->descriptor_set = GraphicsSystem::descriptor_pool.allocate_descriptor_sets(
        shader->pipeline.descriptor_set_layout,
        GraphicsSystem::frames_in_flight);

    vertex_module.destroy();
    fragment_module.destroy();

    return shader;
}