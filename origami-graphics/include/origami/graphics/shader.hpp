#pragma once

#include <vector>
#include <iostream>
#include <sokol_gfx.h>

class Uniform
{
public:
    std::string name;
    sg_uniform_type type;
};

class Shader
{
    friend class GraphicsSystem;

public:
    struct Descriptor
    {
        struct Uniforms
        {
            size_t size = 0;
            std::vector<Uniform> uniforms = {};
        };
        struct Image
        {
            std::string name;
            sg_image_type type;
            sg_image_sample_type sample_type;
        };

        sg_cull_mode cull_mode = SG_CULLMODE_FRONT;
        sg_primitive_type primitive_type = SG_PRIMITIVETYPE_TRIANGLES;
        Uniforms uniforms_vs = {};
        Uniforms uniforms_fs = {};
        std::vector<Image> images = {};
        std::vector<sg_vertex_format> vertex_formats = {
            SG_VERTEXFORMAT_FLOAT3,
            SG_VERTEXFORMAT_FLOAT3,
            SG_VERTEXFORMAT_FLOAT2,
        };
        sg_pixel_format depth_format = SG_PIXELFORMAT_DEPTH;
    };

    Shader();

    ~Shader();

    static Shader *from_file(const std::string &path, Descriptor descriptor);

private:
    sg_shader shader;
    sg_pipeline pipeline;
};
