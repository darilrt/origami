#pragma once

#include <unordered_map>
#include <memory>

#include "type_id.hpp"
#include "resources.hpp"

class EngineState
{
public:
    template <typename T>
    inline T &get_resource()
    {
        return *get_resource_ptr<T>();
    }

    template <typename T>
    inline T *get_resource_ptr()
    {
        return static_cast<T *>(resources[TypeID<T>::value()].get());
    }

    template <typename T>
    inline void init_resource()
    {
        resources[TypeID<T>::value()] = std::make_unique<T>();
    }

    void start();

private:
    std::unordered_map<typeid_t, std::unique_ptr<Resource>> resources;
};