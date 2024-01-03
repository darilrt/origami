#include <origami.hpp>

class Game : public Scene
{
public:
    Camera camera;

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();
        window.set_size({1280, 720});
        window.set_vsync(true);

        camera.start(state);
        camera.set_active(state);
        camera.set_orthographic(5, window.get_aspect(), -1, 1);
        camera.set_resolution(window.get_size() / 5.0f);
    }

    void update(EngineState &state, const Update &time) override
    {
    }

    void destroy(EngineState &state) override {}
};

ENTRY_POINT(Game)