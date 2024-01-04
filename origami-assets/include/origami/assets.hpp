#pragma once

#include <origami/core.hpp>
#include <unordered_map>
#include <string>

template <typename T>
concept Asset = requires(const std::string &path) {
    {
        T::load_asset(path)
    } -> std::same_as<T *>;
};

template <typename T>
using AssetArray = std::unordered_map<std::string, Shared<T>>;

class AssetManager : public Resource
{
public:
    void init(EngineState &state) override {}

    template <Asset T>
    Shared<T> get(const std::string &path)
    {
        AssetArray<T> &array = _get_array<T>();

        if (!array.contains(path))
        {
            T *asset = T::load_asset(path);
            array[path] = Shared<T>(asset);
        }

        return array[path];
    }

private:
    template <typename T>
    AssetArray<T> &_get_array()
    {
        static AssetArray<T> array;
        return array;
    }
};