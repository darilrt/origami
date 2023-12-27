#include <memory>
#include <iostream>

#include <origami/core.hpp>
#include <origami/window.hpp>
#include <origami/event.hpp>
#include <origami/gl.hpp>
#include <origami/assets.hpp>

class Game : public Resource
{
public:
    void init(EngineState &state) override
    {
        auto &es = state.get_resource<EventSystem>();
        es.regist<Start>([&](EngineState &state, void *payload)
                         { this->start(state); });

        es.regist<Update>([&](EngineState &state, void *payload)
                          { this->update(state, *static_cast<Update *>(payload)); });
    }

    void start(EngineState &state)
    {
        auto &window = state.get_resource<Window>();
        window.set_size({1280, 720});
        window.set_title("Origami");

        auto &assets = state.get_resource<AssetManager>();

        assets.load<File>("./assets/shaders/triangle.glsl");
    }

    void update(EngineState &state, Update &time)
    {
        std::cout << "FPS: " << (1.0f / time.delta_time) << std::endl;
    }
};

int main()
{
    auto state = std::make_unique<EngineState>();
    state->init_resource<AssetManager>();
    state->init_resource<EventSystem>();
    state->init_resource<Window>();
    state->init_resource<GraphicsSystem>();
    state->init_resource<Game>();
    state->start();

    state->get_resource<Window>().run(*state);
    return 0;
}
