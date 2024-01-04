#include <origami.hpp>

class Player : public Entity
{
public:
    Transform2D transform{
        .position = {0, 0},
        .rotation = 0,
        .scale = {1, 1},
    };
    Sprite sprite{
        .transform = {
            .parent = &transform,
            .position = {0, 0.45},
            .rotation = 0,
            .scale = {1, 1},
        },
    };
    Camera camera;

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();
        camera.start(state);
        camera.set_active(state);
        camera.set_orthographic(5, window.get_aspect(), -1, 1);
        camera.set_resolution(window.get_size() / 5.0f);
        camera.set_clear_color({0.5f, 0.5f, 0.5f, 1.0f});

        auto &assets = state.get_resource<AssetManager>();
        sprite.sprite = assets.get<Texture>("assets/textures/sword.png");
        sprite.start(state);
    }

    void update(EngineState &state, const Update &time) override
    {
        transform.rotation += 0.5f * time.delta_time;
        sprite.update(state, time);
        camera.update(state, time);
    }

    void destroy(EngineState &state) override
    {
    }
};

class Game : public Scene
{
public:
    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();
        window.set_size({1280, 720});
        window.set_vsync(true);

        group.create<Player>();
        group.start(state);
    }

    void update(EngineState &state, const Update &time) override
    {
        group.update(state, time);
    }

    void destroy(EngineState &state) override {}
};

ENTRY_POINT(Game)