#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>

#include "origami/window/enums.hpp"

class Input : public Resource
{
public:
    void init(EngineState &state);

    inline bool key_down(KeyCode key) { return keys_down[(uint16_t)key]; }

    inline bool key_up(KeyCode key) { return keys_up[(uint16_t)key]; }

    inline bool key_pressed(KeyCode key) { return keys_pressed[(uint16_t)key]; }

    inline bool mouse_button_down(MouseButton button) { return mouse_buttons_down[(uint8_t)button]; }

    inline bool mouse_button_up(MouseButton button) { return mouse_buttons_up[(uint8_t)button]; }

    inline Vec2 get_mouse_position() { return mouse_position; }

    inline Vec2 get_mouse_delta() { return mouse_delta; }

private:
    bool keys_down[256];
    bool keys_up[256];
    bool keys_pressed[256];

    bool mouse_buttons_down[8];
    bool mouse_buttons_up[8];

    Vec2 mouse_position;
    Vec2 mouse_delta;
};