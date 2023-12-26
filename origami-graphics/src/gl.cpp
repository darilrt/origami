
#include <origami/event.hpp>
#include <origami/window.hpp>
#include <sokol_gfx.h>
#include <sokol_log.h>

#include <iostream>

#include "origami/gl.hpp"

class State
{
public:
    sg_pass_action clear_pass;
};

void GraphicsSystem::init(EngineState &state)
{
    auto &window = state.get_resource<Window>();
    auto &es = state.get_resource<EventSystem>();

    State *st = new State;
    st->clear_pass = {0};
    st->clear_pass.colors[0].load_action = SG_LOADACTION_CLEAR;
    st->clear_pass.colors[0].clear_value = {0.1f, 0.1f, 0.1f, 1.0f};

    es.regist<Start>([](EngineState &state, void *_)
                     {
        sg_desc desc = {
            .logger = slog_func,
        };
        sg_setup(&desc); });

    es.regist<Render>([&](EngineState &state, void *_)
                      {
        sg_begin_default_pass(st->clear_pass, window.get_size().x, window.get_size().y);
        sg_end_pass();
        sg_commit(); });
}