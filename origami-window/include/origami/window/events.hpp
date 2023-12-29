#pragma once

#include <origami/event.hpp>

#include "origami/window/enums.hpp"

// Life cycle events
Event(PreStart);
Event(Start);
Event(PreUpdate);
Event(Update {
    float delta_time;
    float life_time;
});
Event(PostUpdate);
Event(Render);
Event(Stop);

// Window events
Event(WindowResize {
    int width;
    int height;
});
Event(WindowClose);

// Keyboard events
Event(KeyDown {
    KeyCode key_code;
});
Event(KeyUp {
    KeyCode key_code;
});

// Mouse events
Event(MouseMove {
    int x;
    int y;
    int dx;
    int dy;
});
Event(MouseButtonDown {
    MouseButton button;
});
Event(MouseButtonUp {
    MouseButton button;
});
Event(MouseScroll {
    int x;
    int y;
});