#pragma once

#include <origami/core.hpp>
#include <origami/event.hpp>
#include <origami/math.hpp>

class Window : public Resource
{
public:
    void init(EngineState &state);

    inline Vec2 get_size() { return size; }

    void set_size(Vec2 size);

private:
    void *window;
    Vec2 size = {800, 600};
};