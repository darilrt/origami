#pragma once

#include <vector>
#include <iostream>
#include <origami/gfx.hpp>

class Shader
{
    friend class GraphicsSystem;

public:
    Pipeline pipeline;

    Shader();

    ~Shader();

    static Shader *load_asset(const std::string &path);
};
