#pragma once

#include <origami/graphics/shader.hpp>
#include <origami/math.hpp>
#include <origami/gfx.hpp>

#include "origami/graphics/texture.hpp"

class Material
{
public:
    static const std::string asset_type;

    std::unordered_map<uint32_t, Unique<Buffer>> _buffers;
    std::unordered_map<std::string, Shared<Texture>> _textures;
    Shared<Shader> shader;

    static Material *load_asset(const std::string &path, AssetManager &asset_manager);

    bool exists_uniform(const std::string &uniform)
    {
        return shader->_uniform_buffers.find(uniform) != shader->_uniform_buffers.end();
    }

    void set_uniform(const std::string &uniform, const std::string &name, const void *data, size_t size);

    template <typename T>
    void set_uniform(const std::string &name, const T &data)
    {
        set_uniform("Material", name, &data, sizeof(T));
    }

    void set_texture(const std::string &name, Shared<Texture> texture);

    void bind();
};