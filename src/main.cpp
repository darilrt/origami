#include <origami.hpp>
#include <origami/gfx.hpp>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

class CameraOrbitController
{
public:
    Shared<Camera> camera;
    Shared<Transform> transform = new_shared<Transform>();

    bool is_dragging = false;

    void update(EngineState &state, const Update &time)
    {
        auto &input = state.get_resource<Input>();

        if (input.key_pressed(KeyCode::R))
        {
            if (!is_dragging)
            {
                is_dragging = true;
            }

            if (is_dragging)
            {
                Vec2 delta = input.get_mouse_delta() * 10.0f * time.delta_time;
                transform->rotation = Quat::from_euler({delta.y, 0, delta.x}) * transform->rotation;
                camera->transform.position = transform->forward() * 2.0f;
                camera->transform.look_at(transform->position);
                camera->transform.rotation = transform->rotation.inverse();
            }
        }
        else
        {
            is_dragging = false;
        }
    }
};

class Game : public Scene
{
public:
    Shared<GraphicEntity> entity;

    Shared<Transform> transform = new_shared<Transform>();
    Shared<Camera> camera = new_shared<Camera>();

    CameraOrbitController controller{
        .camera = camera,
    };

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();
        window.set_size({1280, 720});

        auto &assets = state.get_resource<AssetManager>();
        auto &gs = state.get_resource<GraphicsSystem>();

        float f = sin(math::rad(60)) / 2.0f;

        entity = gs.create_entity();
        entity->model = Mat4::identity();
        entity->mesh = Shared<Mesh>(new Mesh({
            {{0.0f, 0.5f, 0.0f}, {1.0, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{f, -0.25f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{-f, -0.25f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        }));
        entity->mesh = Shared<Mesh>(primitive::torus());
        entity->material = assets.get<Material>("1a68269c-821e-916d-f76f-e005015ba175");

        camera->start(state);
        camera->set_perspective(math::rad(45), 0.1f, 100.0f);
        camera->set_resolution(window.get_size());
        camera->set_active(state);
        camera->transform.position = {0, 0, 3.0f};
    }

    void update(EngineState &state, const Update &time) override
    {
        static auto &window = state.get_resource<Window>();
        static float timer = 0;
        timer += time.delta_time;
        static int fps = 0;
        fps++;

        if (timer >= 1.0)
        {
            window.set_title("fps: " + std::to_string(fps));
            fps = 0;
            timer = 0;
        }

        static auto &input = state.get_resource<Input>();

        transform->rotation = Quat::from_euler({input.key_axis(KeyCode::A, KeyCode::D) * time.delta_time,
                                                input.key_axis(KeyCode::S, KeyCode::W) * time.delta_time,
                                                input.key_axis(KeyCode::E, KeyCode::Q) * time.delta_time}) *
                              transform->rotation;

        entity->material->set_uniform("Environment", "camera", &camera->transform.position, sizeof(Vec3));

        entity->model = transform->get_matrix();

        controller.update(state, time);
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
    state->init_resource<Window>();
    state->start();

    state->get_resource<SceneSystem>().load<Game>();
    state->get_resource<Window>().run(*state);
}