#pragma once

#include <vector>
#include <iostream>

class Shader
{
    friend class GraphicsSystem;

public:
    Shader();

    ~Shader();

    static Shader *load_asset(const std::string &path);

private:
};
