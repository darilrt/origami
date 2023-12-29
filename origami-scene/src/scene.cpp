#include <iostream>
#include <origami/event.hpp>
#include <origami/window.hpp>

#include "origami/scene.hpp"

void SceneSystem::init(EngineState &state)
{
    auto &es = state.get_resource<EventSystem>();

    es.regist<Start>(std::bind(&SceneSystem::_start, this, std::placeholders::_1, std::placeholders::_2));

    es.regist<Update>(std::bind(&SceneSystem::_update, this, std::placeholders::_1, std::placeholders::_2));
}

void SceneSystem::_start(EngineState &state, void *payload)
{
    if (scene)
        scene->start(state);
}

void SceneSystem::_update(EngineState &state, void *payload)
{
    auto &time = *static_cast<Update *>(payload);

    if (scene)
        scene->update(state, time);
}

void EntityGroup::start(EngineState &state)
{
    for (auto &entity : _entities)
        entity->start(state);
}

void EntityGroup::update(EngineState &state, const Update &time)
{
    for (auto &entity : _entities)
        entity->update(state, time);
}
