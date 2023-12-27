#pragma once

#include <origami/core.hpp>

class Asset
{
public:
    virtual void load(const std::string &path) = 0;
};

class AssetManager : public Resource
{
public:
    void init(EngineState &state) override
    {
        std::cout << "AssetManager::init" << std::endl;
    }

    template <typename T>
    T &load(const std::string &path)
    {
        auto asset = std::make_unique<T>();
        asset->load(path);
        return *asset;
    }
};