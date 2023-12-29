#include "origami/window/events.hpp"
#include "origami/input.hpp"

void Input::init(EngineState &state)
{
    auto &es = state.get_resource<EventSystem>();

    es.regist<KeyDown>([&](EngineState &state, void *payload)
                       { this->keys_down[(uint16_t) static_cast<KeyDown *>(payload)->key_code] = true;
                         this->keys_pressed[(uint16_t) static_cast<KeyDown *>(payload)->key_code] = true; });

    es.regist<KeyUp>([&](EngineState &state, void *payload)
                     { this->keys_up[(uint16_t) static_cast<KeyUp *>(payload)->key_code] = true;
                       this->keys_pressed[(uint16_t) static_cast<KeyUp *>(payload)->key_code] = false; });

    es.regist<MouseButtonDown>([&](EngineState &state, void *payload)
                               { this->mouse_buttons_down[(uint8_t) static_cast<MouseButtonDown *>(payload)->button] = true; });

    es.regist<MouseButtonUp>([&](EngineState &state, void *payload)
                             { this->mouse_buttons_up[(uint8_t) static_cast<MouseButtonUp *>(payload)->button] = true; });

    es.regist<MouseMove>([&](EngineState &state, void *payload)
                         {
                             auto *event = static_cast<MouseMove *>(payload);
                             this->mouse_position = {(float) event->x, (float)event->y};
                             this->mouse_delta = {(float)event->dx, (float)event->dy}; });

    es.regist<MouseScroll>([&](EngineState &state, void *payload)
                           {
                               auto *event = static_cast<MouseScroll *>(payload);
                               this->mouse_delta = {(float)event->x, (float)event->y}; });

    es.regist<PostUpdate>([&](EngineState &state, void *payload)
                          {
                            std::fill(std::begin(this->keys_down), std::end(this->keys_down), false);
                            std::fill(std::begin(this->keys_up), std::end(this->keys_up), false);
                            std::fill(std::begin(this->mouse_buttons_down), std::end(this->mouse_buttons_down), false);
                            std::fill(std::begin(this->mouse_buttons_up), std::end(this->mouse_buttons_up), false);
                            this->mouse_delta = {0, 0}; });
}
