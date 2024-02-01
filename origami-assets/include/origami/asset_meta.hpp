#pragma once

#include <origami/core.hpp>
#include <toml.hpp>
#include <string>

class AssetMeta
{
public:
    std::string path;
    std::string uuid;
    std::string type;
    std::string name;

    toml::value data;

    static AssetMeta load_asset_meta(const std::string &path, const std::string &type);
};