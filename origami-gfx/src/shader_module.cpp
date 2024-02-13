#include <GL/glew.hpp>
#include <GL/gl.h>
#include <iostream>

#include "origami/gfx/shader_module.hpp"

ShaderModule::ShaderModule(ShaderType type)
{
    _id = glCreateShader((GLenum)type);
}

ShaderModule::~ShaderModule()
{
    glDeleteShader(_id);
}

void ShaderModule::set_source(const char *source)
{
    glShaderSource(_id, 1, &source, NULL);
}

void ShaderModule::compile()
{
    glCompileShader(_id);

    int success;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(_id, 512, NULL, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }
}