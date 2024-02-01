#include <iostream>
#include <fstream>
#include <toml.hpp>
#include <origami/utils/uuid.hpp>

#include "origami/asset_meta.hpp"

AssetMeta AssetMeta::load_asset_meta(const std::string &path, const std::string &type)
{
    AssetMeta meta;
    meta.path = "assets/" + path + ".toml";
    meta.type = type;

    std::ifstream file(meta.path);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << meta.path << std::endl;
        return meta;
    }

    try
    {
        meta.data = toml::parse(file);
    }
    catch (toml::syntax_error &e)
    {
        std::cerr << "Failed to parse file: " << meta.path << std::endl;
        std::cerr << e.what() << std::endl;
        return meta;
    }

    file.close();

    if (!meta.data.contains("metadata"))
    {
        std::cerr << "Metadata missing for asset: " << meta.path << std::endl;
        return meta;
    }

    auto &metadata = meta.data.at("metadata");

    if (meta.type != metadata.at("type").as_string().str)
    {
        std::cerr << "Type mismatch for asset: " << meta.path << std::endl;
        return meta;
    }

    if (!metadata.contains("uuid"))
    {
        metadata["uuid"] = UUID().get_uuid();

        std::ofstream out(meta.path);
        out << meta.data;
        out.close();
    }

    meta.uuid = metadata.at("uuid").as_string().str;

    return meta;
}