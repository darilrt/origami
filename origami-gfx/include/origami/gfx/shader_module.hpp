#pragma once

#include <string>

class ShaderModule
{
public:
    void *id = 0;
    void *device = 0;

    struct Parameters
    {
        void *device = 0;
        std::string file_path = "";
    };

    ShaderModule() = default;

    ShaderModule(const Parameters &parameters);

    void destroy();
};