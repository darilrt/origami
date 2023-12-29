#pragma once

#include <vector>
#include <origami/core.hpp>
#include <origami/window.hpp>

#include "origami/scene/entity.hpp"

class Scene
{
public:
    EntityGroup group;

    Scene() = default;
    ~Scene() = default;

    virtual void start(EngineState &state) = 0;

    virtual void update(EngineState &state, const Update &time) = 0;

    virtual void destroy(EngineState &state) = 0;
};
