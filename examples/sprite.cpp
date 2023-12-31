#include <origami.hpp>

class Game : public Scene
{
public:
    Sprite sprite;

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();
        window.set_vsync(true);

        auto &graphics = state.get_resource<GraphicsSystem>();
        graphics.set_view(Mat4::identity());

        Vec2 half = window.get_size() / 2.0f / 100;
        graphics.set_projection(Mat4::ortho(-half.x, half.x, -half.y, half.y, -1.0f, 1.0f));

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

        sprite.update(state, time);
    }

    void destroy(EngineState &state) override {}
};

ENTRY_POINT(Game)