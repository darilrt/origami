#pragma once

#include <origami/core.hpp>

class GraphicsSystem : public Resource
{
    class State;

public:
    GraphicsSystem();

    ~GraphicsSystem();

    void init(EngineState &state);

    void set_clear_color(Vec4 color);

private:
    State *gs_state = nullptr;
};