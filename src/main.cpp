#include <origami.hpp>

class MeshRenderer
{
public:
    Transform transform;
    Shared<Mesh> mesh;
    Shared<Material> material;
    Shared<GraphicEntity> entity;

    void start(EngineState &state)
    {
        auto &graphics = state.get_resource<GraphicsSystem>();
        entity = graphics.create_entity();
        entity->mesh = mesh;
        entity->material = material;
        entity->model = transform.get_matrix();
    }

    void update(EngineState &state, const Update &time)
    {
        entity->model = transform.get_matrix();
    }
};

class Player : public Entity
{
public:
    Transform transform;
    Camera camera;

    Unique<MeshRenderer> renderer;

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();

        camera.start(state);
        camera.set_active(state);
        camera.set_perspective(math::rad(60.0), 0.1f, 100.0f);
        camera.set_resolution(window.get_size());
        camera.set_clear_color({0.5f, 0.5f, 0.5f, 1.0f});
        camera.transform.position = {0, 0, 5};

        renderer = new_unique<MeshRenderer>();
        renderer->mesh = Shared<Mesh>(primitive::quad());
        renderer->material = new_shared<LitMaterial>();
        renderer->start(state);
    }

    void update(EngineState &state, const Update &time) override
    {
        camera.transform.rotation = Quat::from_euler({0, math::half_pi / 2.0, 0});
        renderer->update(state, time);
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