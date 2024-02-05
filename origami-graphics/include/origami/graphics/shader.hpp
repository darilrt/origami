#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>
#include <origami/gfx.hpp>
#include <origami/assets.hpp>

class Shader
{
    friend class GraphicsSystem;

public:
    static std::string asset_type;

    uint32_t uniform_size;
    Pipeline pipeline;
    std::vector<DescriptorSet> descriptor_set;
    std::unordered_map<std::string, uint32_t> offsets;

    static Shader *load_asset(const std::string &path, AssetManager &asset_manager);
};
