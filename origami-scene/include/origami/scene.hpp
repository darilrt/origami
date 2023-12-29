#pragma once

#include <origami/core.hpp>

#include "origami/scene/scene.hpp"
#include "origami/scene/entity.hpp"

class SceneSystem : public Resource
{
public:
    void init(EngineState &state) override;

    template <typename T>
    void load()
    {
        scene = std::make_unique<T>();
    }

private:
    std::unique_ptr<Scene> scene;

    void _start(EngineState &state, void *);

    void _update(EngineState &state, void *);
};
