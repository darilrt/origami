#include <GL/glew.hpp>
#include <GL/gl.h>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <origami/assets.hpp>
#include <origami/gfx.hpp>
#include <toml++/toml.hpp>

#include "origami/graphics/graphics_system.hpp"
#include "origami/graphics/shader.hpp"

std::string Shader::asset_type = "Graphics/Shader";

// type, format, size, alignment
std::unordered_map<std::string, std::tuple<glid_t, int, int>> format_map = {
    {"int", {GL_INT, 4, 4}},
    {"float", {GL_FLOAT, 4, 4}},
    {"vec2", {GL_FLOAT_VEC2, 8, 8}},
    {"vec3", {GL_FLOAT_VEC3, 12, 16}},
    {"vec4", {GL_FLOAT_VEC4, 16, 16}},
    {"mat4", {GL_FLOAT_MAT4, 64, 64}},
    {"sampler2D", {GL_SAMPLER_2D, 4, 4}},
    {"samplerCube", {GL_SAMPLER_CUBE, 4, 4}},
};

void Shader::use()
{
    glUseProgram(_id);
}

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

    std::string vertex_path = asset_manager.assets[vertex_uuid].first;
    std::string fragment_path = asset_manager.assets[fragment_uuid].first;

    std::ifstream vertex_file(vertex_path);
    std::string vertex_source((std::istreambuf_iterator<char>(vertex_file)), std::istreambuf_iterator<char>());

    std::ifstream fragment_file(fragment_path);
    std::string fragment_source((std::istreambuf_iterator<char>(fragment_file)), std::istreambuf_iterator<char>());

    Shader *shader = new Shader();

    ShaderModule *vertex_module = new ShaderModule(ShaderType::Vertex);
    vertex_module->set_source(vertex_source.c_str());
    vertex_module->compile();

    ShaderModule *fragment_module = new ShaderModule(ShaderType::Fragment);
    fragment_module->set_source(fragment_source.c_str());
    fragment_module->compile();

    shader->_id = glCreateProgram();
    glAttachShader(shader->_id, vertex_module->_id);
    glAttachShader(shader->_id, fragment_module->_id);
    glLinkProgram(shader->_id);

    int success;

    glGetProgramiv(shader->_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shader->_id, 512, NULL, infoLog);
        std::cerr << "Shader linking failed: " << infoLog << std::endl;
    }

    if (data.contains("bindings"))
    {
        toml::array &bindings = *data["bindings"].as_array();

        for (const auto &binding : bindings)
        {
            const toml::table &uniform_table = *binding.as_table();

            UnifrormBuffers buffer;
            buffer.name = uniform_table["name"].as_string()->get();
            buffer.binding = uniform_table["binding"].as_integer()->get();
            buffer.index = glGetUniformBlockIndex(shader->_id, buffer.name.c_str());
            buffer.size = 0;

            const toml::array &uniforms = *uniform_table["uniforms"].as_array();

            for (const auto &uniform : uniforms)
            {
                const toml::table &uniform_table = *uniform.as_table();

                std::string type = uniform_table["type"].as_string()->get();
                std::string name = uniform_table["name"].as_string()->get();

                auto [gl_type, size, alignment] = format_map[type];

                int pos = round((float)buffer.size / (float)alignment + 0.4999f) * alignment;

                buffer.size = pos + size;
                buffer.offsets[name] = pos;
            }

            shader->_uniform_buffers[buffer.name] = buffer;
        }
    }

    return shader;
}