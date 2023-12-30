#include <origami.hpp>
#include <memory>
#include <iostream>
#include <string>

class Game : public Scene
{
public:
    Sprite sprite;

    void start(EngineState &state) override
    {
        auto &graphics = state.get_resource<GraphicsSystem>();
        graphics.set_view(Mat4::identity());
        graphics.set_projection(Mat4::ortho(-3, 3, -2, 2, -1, 1));

        auto &assets = state.get_resource<AssetManager>();

        sprite.sprite = &assets.get<Texture>("assets/textures/gridbox.png"),
        sprite.start(state);
    }

    void update(EngineState &state, const Update &time) override
    {
        sprite.update(state, time);
    }

    void destroy(EngineState &state) override {}
};

ENTRY_POINT(Game)