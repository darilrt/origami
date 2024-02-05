#pragma once

#include <origami/graphics/shader.hpp>
#include <origami/math.hpp>

#include "origami/graphics/texture.hpp"

class Material
{
public:
    Buffer uniform_buffer;
    Shared<Shader> shader;
    static const std::string asset_type;

    static Material *load_asset(const std::string &path, AssetManager &asset_manager);

    void set_uniform(const std::string &name, const void *data, size_t size);

    template <typename T>
    void set_uniform(const std::string &name, const T &data)
    {
        set_uniform(name, &data, sizeof(T));
    }
};