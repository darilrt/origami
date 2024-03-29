#pragma once

#include <origami/core.hpp>
#include <origami/event.hpp>
#include <origami/math.hpp>

#include "origami/window/enums.hpp"
#include "origami/window/events.hpp"

class Window : public Resource
{
public:
    void init(EngineState &state);

    void run(EngineState &state);

    inline Vec2 get_size() { return size; }

    inline float get_aspect() { return size.x / size.y; }

    void set_size(Vec2 size);

    void set_title(const std::string &title);

    void set_vsync(bool vsync);

    void set_fullscreen(bool fullscreen);

private:
    void *window;
    Vec2 size = {800, 600};
};