#include <iostream>
#include <filesystem>
#include <fstream>
#include <toml.hpp>
#include <origami/asset_meta.hpp>
#include <origami/gfx.hpp>

#include "origami/graphics/graphics_system.hpp"
#include "origami/graphics/shader.hpp"

Shader::Shader()
{
}

Shader::~Shader()
{
}

Shader *Shader::load_asset(const std::string &path)
{
    AssetMeta meta = AssetMeta::load_asset_meta(path, "Graphics/Shader");

    if (!meta.data.contains("info"))
    {
        std::cerr << "Info missing for shader: " << meta.path << std::endl;
        return nullptr;
    }

    auto &info = meta.data.at("info");

    if (!info.contains("vertex") || !info.contains("fragment"))
    {
        std::cerr << "Vertex or fragment missing for shader: " << meta.path << std::endl;
        return nullptr;
    }

    std::string vertex_path = "assets/" + info.at("vertex").as_string().str;
    std::string fragment_path = "assets/" + info.at("fragment").as_string().str;

    if (!std::filesystem::exists(vertex_path))
    {
        std::cerr << "Vertex shader missing: " << vertex_path << std::endl;
        return nullptr;
    }

    if (!std::filesystem::exists(fragment_path))
    {
        std::cerr << "Fragment shader missing: " << fragment_path << std::endl;
        return nullptr;
    }

    ShaderModule vertex_module = ShaderModule::create({
        .device = GraphicsSystem::vk_device.device,
        .file_path = vertex_path,
    });

    ShaderModule fragment_module = ShaderModule::create({
        .device = GraphicsSystem::vk_device.device,
        .file_path = fragment_path,
    });

    Shader *shader = new Shader();

    shader->pipeline = Pipeline::create({
        .device = GraphicsSystem::vk_device.device,
        .vs_module = vertex_module,
        .fs_module = fragment_module,
        .render_pass = GraphicsSystem::render_pass,
    });

    return nullptr;
}