#pragma once

#include <origami/core.hpp>
#include <origami/window.hpp>

class Entity
{
public:
    Entity() = default;

    virtual void start(EngineState &state) = 0;

    virtual void update(EngineState &state, const Update &time) = 0;

    virtual void destroy(EngineState &state) = 0;
};

class EntityGroup
{
public:
    EntityGroup() = default;
    ~EntityGroup() = default;

    void start(EngineState &state);

    void update(EngineState &state, const Update &time);

    template <typename T>
    T &create()
    {
        T *ref = new T;
        _entities.push_back(ref);
        return *ref;
    }

private:
    std::vector<Entity *> _entities;
};