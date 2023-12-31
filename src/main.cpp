#include <origami.hpp>

class Game : public Scene
{
public:
    Camera camera;
    Sprite sprite;

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();
        window.set_size({1280, 720});
        window.set_vsync(true);

        camera.resolution = window.get_size() / 5.0f;
        camera.start(state);
        camera.set_active(state);
        camera.set_orthographic(5, window.get_aspect(), -1, 1);

        auto &assets = state.get_resource<AssetManager>();
        sprite.sprite = assets.get<Texture>("assets/textures/gridbox.png"),
        sprite.start(state);
    }

    void update(EngineState &state, const Update &time) override
    {
        static Timer timer;
        static int fps = 0;

        if (timer.elapsed() > 1)
        {
            timer.reset();
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
        }
        fps++;

        auto &input = state.get_resource<Input>();

        if (input.key_pressed(KeyCode::A))
            camera.transform.position.x -= 10.0 * time.delta_time;
        if (input.key_pressed(KeyCode::D))
            camera.transform.position.x += 10.0 * time.delta_time;
        if (input.key_pressed(KeyCode::W))
            camera.transform.position.y += 10.0 * time.delta_time;
        if (input.key_pressed(KeyCode::S))
            camera.transform.position.y -= 10.0 * time.delta_time;

        sprite.transform.rotation += 1.0f * time.delta_time;
        sprite.update(state, time);
        camera.update(state, time);
    }

    void destroy(EngineState &state) override {}
};

ENTRY_POINT(Game)