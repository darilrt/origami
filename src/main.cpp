#include <origami.hpp>
#include <origami/gfx.hpp>

class Game : public Scene
{
public:
    Shared<Camera> camera = new_shared<Camera>();
    Shared<Sprite> sprite = new_shared<Sprite>();

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();
        window.set_vsync(true);
        window.set_size({1280, 720});

        camera->start(state);
        camera->set_orthographic(5.0f, -1.0f, 1.0f);
        camera->set_resolution(window.get_size());
        camera->set_active(state);

        auto &asset = state.get_resource<AssetManager>();
        // sprite->sprite = asset.get<Texture>("built-in/texture/gridbox");

        sprite->start(state);
    }

    void update(EngineState &state, const Update &time) override
    {
        camera->update(state, time);
    }

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
    state->init_resource<UI>();
    state->init_resource<Window>();
    state->start();

    state->get_resource<SceneSystem>().load<Game>();
    state->get_resource<Window>().run(*state);
}