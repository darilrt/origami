#include <origami.hpp>
#include <origami/gfx.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

class Game : public Scene
{
public:
    void start(EngineState &state) override
    {
        // auto &assets = state.get_resource<AssetManager>();

        // Shared<Shader> sh = assets.get<Shader>("shaders/spirv/shader");
    }

    void update(EngineState &state, const Update &time) override {}

    void destroy(EngineState &state) override {}
};

int main()
{
    auto state = std::make_unique<EngineState>();
    state->init_resource<AssetManager>();
    state->init_resource<GraphicsSystem>();
    state->init_resource<EventSystem>();
    state->init_resource<Input>();
    state->init_resource<SceneSystem>();
    state->init_resource<Window>();
    state->start();

    state->get_resource<SceneSystem>().load<Game>();
    state->get_resource<Window>().run(*state);
}