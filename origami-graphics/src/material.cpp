#include <GL/glew.hpp>
#include <GL/gl.h>
#include <origami/assets.hpp>
#include <toml++/toml.h>

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

    Material *material = new Material;
    material->shader = shader;

    for (auto &uniform : shader->_uniform_buffers)
    {
        material->_buffers[uniform.second.binding] = std::make_unique<Buffer>(BufferType::Uniform);
        material->_buffers[uniform.second.binding]->set_data(nullptr, uniform.second.size, BufferUsage::Dynamic);
    }

    if (data.contains("textures"))
    {
        toml::table &textures = *data["textures"].as_table();

        for (auto &[name, texture_uuid] : textures)
        {
            Shared<Texture> texture = asset_manager.get<Texture>(texture_uuid.as_string()->get());

            if (!texture)
            {
                std::cerr << "Material file " << path << " references a texture that does not exist" << std::endl;
                continue;
            }

            material->_textures[std::string(name.str())] = texture;
        }
    }

    return material;
}

void Material::set_uniform(const std::string &uniform, const std::string &name, const void *data, size_t size)
{
    if (shader->_uniform_buffers.find(uniform) == shader->_uniform_buffers.end())
    {
        std::cerr << "Uniform \"" << uniform << "\" does not exist in shader" << std::endl;
        return;
    }

    auto &uniforms = shader->_uniform_buffers[uniform];

    if (uniforms.offsets.find(name) == uniforms.offsets.end())
    {
        std::cerr << "Uniform \"" << name << "\" does not exist in uniform buffer" << std::endl;
        return;
    }

    auto offset = uniforms.offsets[name];

    _buffers[uniforms.binding]->set_sub_data(data, size, offset);
}

void Material::set_texture(const std::string &name, Shared<Texture> texture)
{
    _textures[name] = texture;
}

void Material::bind()
{
    shader->use();

    int texture_unit = 0;
    for (auto &texture : _textures)
    {
        texture.second->bind(texture_unit);
        glProgramUniform1i(shader->_id, glGetUniformLocation(shader->_id, texture.first.c_str()), texture_unit);
        texture_unit++;
    }

    for (auto &buffer : _buffers)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, buffer.first, buffer.second->_id);
    }
}