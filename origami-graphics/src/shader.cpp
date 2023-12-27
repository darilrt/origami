#include <iostream>

#include "origami/graphics/shader.hpp"

Shader::Shader()
{
    auto desc = sg_shader_desc{
        .vs = {
            .source =
                R"(
                    #version 330
                    layout(location = 0) in vec3 position;
                    layout(location = 1) in vec3 normal;
                    layout(location = 2) in vec2 uv;
                    void main() {
                        gl_Position = vec4(position, 1.0);
                    }
                )",
        },
        .fs = {
            .source =
                R"(
                    #version 330
                    out vec4 frag_color;
                    void main() {
                        frag_color = vec4(1.0, 0.0, 0.0, 1.0);
                    }
                )",
        },
    };

    shader = sg_make_shader(desc);

    if (shader.id == SG_INVALID_ID)
    {
        std::cout << "Failed to create shader" << std::endl;
    }
}

Shader::Shader(const std::string &vertex, const std::string &fragment)
{
}

void Shader::_load_shader(const std::string &vertex, const std::string &fragment)
{
}