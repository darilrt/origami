#include "origami/shader.hpp"

Shader::Shader(const std::string &vertex, const std::string &fragment)
{
    _load_shader(vertex, fragment);
}

void Shader::_load_shader(const std::string &vertex, const std::string &fragment)
{
    shader = sg_make_shader(sg_shader_desc{
        .vs = {.source = vertex.c_str()},
        .fs = {.source = fragment.c_str()},
    });
}