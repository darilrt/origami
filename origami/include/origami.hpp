#pragma once

#include <origami/window.hpp>
#include <origami/input.hpp>
#include <origami/event.hpp>
#include <origami/graphics.hpp>
#include <origami/assets.hpp>
#include <origami/scene.hpp>

#define ENTRY_POINT(T)  \
    int main()          \
    {                   \
        start_app<T>(); \
        return 0;       \
    }

template <typename T>
void start_app()
{
    auto state = std::make_unique<EngineState>();
    state->init_resource<AssetManager>();
    state->init_resource<EventSystem>();
    state->init_resource<Input>();
    state->init_resource<SceneSystem>();
    state->init_resource<Window>();
    state->init_resource<GraphicsSystem>();
    state->start();
    state->get_resource<SceneSystem>().load<T>();
    state->get_resource<Window>().run(*state);
}