#pragma once

#include <vector>
#include <iostream>
#include <sokol_gfx.h>

class Shader
{
    friend class GraphicsSystem;

public:
    Shader();

    ~Shader();

    static Shader *load_asset(const std::string &path);

private:
};
