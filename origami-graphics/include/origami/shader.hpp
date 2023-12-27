#pragma once

#include <iostream>
#include <sokol_gfx.h>

class Shader
{
public:
    Shader(const std::string &vertex, const std::string &fragment);

private:
    void _load_shader(const std::string &vertex, const std::string &fragment);

    sg_shader shader;
};