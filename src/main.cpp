#include <origami.hpp>
#include <origami/gfx.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

class Game : public Scene
{
public:
    Shared<GraphicEntity> entity;

    Transform transform;
    Camera camera;
    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();
        auto &assets = state.get_resource<AssetManager>();
        auto &gs = state.get_resource<GraphicsSystem>();

        entity = gs.create_entity();
        entity->model = Mat4::identity();
        entity->mesh = Shared<Mesh>(new Mesh({
            {{0.0f, -0.5f, 0.0f}, {1.0, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        }));
        entity->material = assets.get<Material>("1a68269c-821e-916d-f76f-e005015ba175");

        camera.start(state);
        camera.set_perspective(math::rad(45), 0.1f, 100.0f);
        camera.set_resolution(window.get_size());
        camera.set_active(state);
        camera.transform.position = {0, 0, 2.0f};
    }

    void update(EngineState &state, const Update &time) override
    {
        static float timer = 0;
        timer += time.delta_time;

        entity->material->set_uniform("time", timer);

        // transform.rotation = Quat::from_euler({time.delta_time, time.delta_time, time.delta_time}) * transform.rotation;
        // transform.scale = Vec3{1, 1, 1} * (0.5f + (std::sin(timer) + 1) * 0.25f);
        // entity->model = transform.get_matrix();

        camera.update(state, time);
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
    state->init_resource<Window>();
    state->start();

    state->get_resource<SceneSystem>().load<Game>();
    state->get_resource<Window>().run(*state);
}