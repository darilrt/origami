#include <memory>
#include <iostream>

#include <origami/core.hpp>
#include <origami/window.hpp>
#include <origami/event.hpp>
#include <origami/gl.hpp>

int main()
{
    auto state = std::make_unique<EngineState>();
    state->init_resource<EventSystem>();
    state->init_resource<Window>();
    state->init_resource<GraphicsSystem>();
    state->start();
    return 0;
}
