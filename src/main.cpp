#include <origami.hpp>
#include <origami/gfx.hpp>

class Game : public Scene
{
public:
    Unique<gfx::State> gfx_state;

    void start(EngineState &state) override
    {
        gfx_state = new_unique<gfx::State>();

        gfx_state->setup({
            .app_name = "Test",
            .app_version = VK_MAKE_VERSION(1, 0, 0),
            .engine_name = "Origami",
            .engine_version = VK_MAKE_VERSION(1, 0, 0),
            .api_version = VK_API_VERSION_1_0,
            .enable_validation_layers = true,
            .validation_layers = {
                "VK_LAYER_KHRONOS_validation",
            },
            .required_extensions = {
                VK_KHR_SURFACE_EXTENSION_NAME,
                VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
            },
        });
    }

    void update(EngineState &state, const Update &time) override {}

    void destroy(EngineState &state) override {}
};

int main()
{
    auto state = std::make_unique<EngineState>();
    state->init_resource<AssetManager>();
    state->init_resource<EventSystem>();
    state->init_resource<Input>();
    state->init_resource<SceneSystem>();
    state->init_resource<Window>();
    state->init_resource<GraphicsSystem>();
    state->init_resource<Debug>();
    state->start();

    state->get_resource<SceneSystem>().load<Game>();
    state->get_resource<Window>().run(*state);
}