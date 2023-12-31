#pragma once

#include <unordered_map>
#include <memory>

#include "origami/core/ptr.hpp"
#include "origami/core/type_id.hpp"
#include "origami/core/resources.hpp"

struct InitializedResources; // Event

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
        resources[TypeID<T>::value()] = new_unique<T>();
    }

    void start();

private:
    std::unordered_map<typeid_t, Unique<Resource>> resources;
};