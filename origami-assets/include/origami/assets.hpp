#pragma once

#include <origami/core.hpp>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

class AssetManager; // Forward declaration

template <typename T>
concept Asset = requires(const std::string &path) {
    T::asset_type;

    {
        T::load_asset(path, std::declval<AssetManager &>())
    } -> std::same_as<T *>;
};

template <typename T>
using AssetArray = std::unordered_map<std::string, Shared<T>>;

class AssetManager : public Resource
{
public:
    std::unordered_map<std::string, std::pair<std::string, std::string>> assets;

    void init(EngineState &state) override;

    void scan(const std::string &path);

    inline bool contains(const std::string &uuid)
    {
        return assets.contains(uuid);
    }

    template <Asset T>
    Shared<T> get(const std::string &uuid)
    {
        if (!assets.contains(uuid))
        {
            std::cout << "Asset \"" + uuid + "\" not found" << std::endl;
            return nullptr;
        }

        auto data = assets[uuid];

        if (data.second != T::asset_type)
        {
            std::cout << "Asset \"" + uuid + "\" is not of type " + T::asset_type << std::endl;
            return nullptr;
        }

        AssetArray<T> &array = get_array<T>();

        std::string path = data.first;

        if (!array.contains(uuid))
        {
            T *asset = T::load_asset(path, *this);
            array[uuid] = Shared<T>(asset);
        }

        return array[uuid];
    }

private:
    template <typename T>
    AssetArray<T> &get_array()
    {
        static AssetArray<T> array;
        return array;
    }
};