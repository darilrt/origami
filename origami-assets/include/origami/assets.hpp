#pragma once

#include <origami/core.hpp>
#include <unordered_map>

template <typename T>
concept Asset = requires(const std::string &path) {
    {
        T::load_asset(path)
    } -> std::same_as<T *>;
};

template <typename T>
using AssetArray = std::unordered_map<std::string, T *>;

class AssetManager : public Resource
{
public:
    void init(EngineState &state) override {}

    template <Asset T>
    T &get(const std::string &path)
    {
        AssetArray<T> &array = _get_array<T>();

        if (array.contains(path))
        {
            return *array[path];
        }

        T *asset = T::load_asset(path);
        array[path] = asset;

        return *asset;
    }

private:
    template <typename T>
    AssetArray<T> &_get_array()
    {
        static AssetArray<T> array;
        return array;
    }
};