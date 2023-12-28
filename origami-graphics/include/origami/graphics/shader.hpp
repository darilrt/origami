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
    Shader();

    ~Shader();

    static Shader *from_file(const std::string &path,
                             size_t uvs_size, std::vector<Uniform> uniforms_vs,
                             size_t ufs_size, std::vector<Uniform> uniforms_fs);

private:
    sg_shader shader;
    sg_pipeline pipeline;
};
