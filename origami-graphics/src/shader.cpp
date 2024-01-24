#include <iostream>
#include <filesystem>
#include <fstream>

#include <toml.hpp>

#include "origami/graphics/shader.hpp"

Shader::Shader()
{
}

Shader::~Shader()
{
}

Shader *Shader::load_asset(const std::string &path)
{
    return nullptr;
}