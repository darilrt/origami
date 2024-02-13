#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>
#include <origami/gfx.hpp>
#include <origami/assets.hpp>

class UnifrormBuffers
{
public:
    std::string name;
    uint32_t binding;
    uint32_t index;
    uint32_t size;
    std::unordered_map<std::string, uint32_t> offsets;
};

class Shader
{
    friend class GraphicsSystem;

public:
    static std::string asset_type;

    glid_t _id;

    std::unordered_map<std::string, UnifrormBuffers> _uniform_buffers;

    void use();

    static Shader *load_asset(const std::string &path, AssetManager &asset_manager);
};
