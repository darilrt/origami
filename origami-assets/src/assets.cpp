#include "origami/assets.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <tuple>
#include <toml++/toml.hpp>
#include <origami/utils/uuid.hpp>

std::string get_type_from_extension(const std::string &ext)
{
    if (ext == ".shader")
        return "Graphics/Shader";
    if (ext == ".spv")
        return "Graphics/ShaderModule";
    if (ext == ".frag" || ext == ".vert" || ext == ".comp" || ext == ".geom" || ext == ".tesc" || ext == ".tese")
        return "Graphics/ShaderSource";
    if (ext == ".mat")
        return "Graphics/Material";
    if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
        return "Graphics/Texture";

    return "";
}

void AssetManager::init(EngineState &state)
{
    scan("assets");
    // scan("built-in");
}

void AssetManager::scan(const std::string &path)
{
    std::cout << "Scanning " << path << std::endl;

    for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        std::string ext = entry.path().extension().string();

        if (ext == ".meta")
        {
            continue;
        }

        std::string meta_path = entry.path().string() + ".meta";

        toml::table meta;

        if (!std::filesystem::exists(meta_path))
        {
            std::ofstream file(meta_path);

            meta = toml::table{
                {"uuid", UUID::generate()},
                {"type", get_type_from_extension(ext)},
            };

            file << meta;
        }
        else
        {
            meta = toml::parse_file(meta_path);
        }

        std::string uuid = meta["uuid"].value_or(UUID::generate());
        std::string type = meta["type"].value_or(get_type_from_extension(ext));

        assets[uuid] = std::make_pair(entry.path().string(), type);
    }
}