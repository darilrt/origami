#include <iostream>
#include <filesystem>
#include <fstream>

#include "origami/graphics/shader.hpp"

Shader::Shader()
{
}

Shader::~Shader()
{
    sg_destroy_shader(shader);
    sg_destroy_pipeline(pipeline);
}

Shader *Shader::from_file(const std::string &path, Shader::Descriptor descriptor)
{
    std::string fs = path + ".fs";
    std::string vs = path + ".vs";
    std::ifstream file(fs);
    if (!file.is_open())
    {
        std::cout << "Failed to open shader file: " << path << std::endl;
        return nullptr;
    }
    std::string fs_source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    file = std::ifstream(vs);
    if (!file.is_open())
    {
        std::cout << "Failed to open shader file: " << path << std::endl;
        return nullptr;
    }
    std::string vs_source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    Shader *shader = new Shader();

    auto shader_desc = sg_shader_desc{
        .vs = {
            .source = vs_source.c_str(),
            .entry = "main",
        },
        .fs = {
            .source = fs_source.c_str(),
            .entry = "main",
        },
    };

    shader_desc.vs.uniform_blocks[0].size = descriptor.uniforms_vs.size;
    int num_uniforms = 0;
    for (auto &uniform : descriptor.uniforms_vs.uniforms)
    {
        shader_desc.vs.uniform_blocks[0].uniforms[num_uniforms++] = {
            .name = uniform.name.c_str(),
            .type = uniform.type,
        };
    }

    shader_desc.fs.uniform_blocks[0].size = descriptor.uniforms_fs.size;
    num_uniforms = 0;
    for (auto &uniform : descriptor.uniforms_fs.uniforms)
    {
        shader_desc.fs.uniform_blocks[0].uniforms[num_uniforms++] = {
            .name = uniform.name.c_str(),
            .type = uniform.type,
        };
    }

    int num_images = 0;
    for (auto &image : descriptor.images)
    {
        shader_desc.fs.images[num_images++] = {
            .used = true,
            .image_type = image.type,
        };
        shader_desc.fs.samplers[num_images - 1] = {
            .used = true,
            .sampler_type = SG_SAMPLERTYPE_FILTERING,
        };
        shader_desc.fs.image_sampler_pairs[num_images - 1] = {
            .used = true,
            .image_slot = num_images - 1,
            .sampler_slot = num_images - 1,
            .glsl_name = image.name.c_str(),
        };
    }

    shader->shader = sg_make_shader(shader_desc);

    if (shader->shader.id == SG_INVALID_ID)
    {
        std::cout << "Failed to create shader from file: " << path << std::endl;
        return nullptr;
    }

    auto pipeline_desc = sg_pipeline_desc{
        .shader = shader->shader,
        .primitive_type = descriptor.primitive_type,
        .cull_mode = descriptor.cull_mode,
    };
    pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
    pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT3;
    pipeline_desc.layout.attrs[2].format = SG_VERTEXFORMAT_FLOAT2;
    pipeline_desc.index_type = SG_INDEXTYPE_UINT32;
    shader->pipeline = sg_make_pipeline(pipeline_desc);

    if (shader->pipeline.id == SG_INVALID_ID)
    {
        std::cout << "Failed to create pipeline from file: " << path << std::endl;
        return nullptr;
    }

    return shader;
}