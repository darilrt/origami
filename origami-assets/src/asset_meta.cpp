#include <iostream>
#include <fstream>
#include <origami/utils/uuid.hpp>
#include <toml++/toml.hpp>

#include "origami/asset_meta.hpp"

AssetMeta AssetMeta::load_asset_meta(const std::string &path, const std::string &type)
{
    return AssetMeta{path, type};
}