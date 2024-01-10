#include <origami.hpp>

class MeshRenderer
{
public:
    Transform transform;
    Shared<GraphicEntity> entity;

    void start(EngineState &state)
    {
        auto &graphics = state.get_resource<GraphicsSystem>();
        entity = graphics.create_entity();

        if (!entity->mesh)
            entity->mesh = Shared<Mesh>(new Mesh({}));

        if (!entity->material)
            entity->material = new_shared<LitMaterial>();

        entity->model = transform.get_matrix();
    }

    void update(EngineState &state, const Update &time)
    {
        entity->model = transform.get_matrix();
    }

    inline Shared<Mesh> get_mesh() const { return entity->mesh; }

    inline Shared<Material> get_material() const { return entity->material; }

    inline void set_mesh(Shared<Mesh> mesh) { entity->mesh = mesh; }

    inline void set_material(Shared<Material> material) { entity->material = material; }
};

class PBRRenderer
{
public:
    Shared<LitMaterial> material = new_shared<LitMaterial>();
    Shared<MeshRenderer> renderer = new_shared<MeshRenderer>();

    void start(EngineState &state)
    {
        auto &assets = state.get_resource<AssetManager>();
        auto texture = assets.get<Texture>("assets/textures/gridbox.png");
        material->set_texture(0, texture->image.get(), texture->sampler.get());

        renderer->start(state);
        renderer->set_mesh(Shared<Mesh>(primitive::cube()));
        renderer->set_material(material);
    }

    void update(EngineState &state, const Update &time)
    {
        renderer->update(state, time);
    }
};
class Player : public Entity
{
public:
    Transform transform;
    Camera camera;

    Unique<PBRRenderer> ground;
    Unique<PBRRenderer> cube;

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();

        camera.start(state);
        camera.set_active(state);
        camera.set_perspective(math::rad(60.0), 0.1f, 100.0f);
        camera.set_resolution(window.get_size());
        camera.set_clear_color({0.1f, 0.11f, 0.10f, 1.0f});
        camera.transform.position = {0, 3, 3};
        camera.transform.rotation = Quat::from_euler({math::rad(45.0f), 0, 0});

        ground = new_unique<PBRRenderer>();
        ground->start(state);
        ground->renderer->set_mesh(Shared<Mesh>(primitive::plane()));
        ground->renderer->transform.scale = {10, 10, 10};

        cube = new_unique<PBRRenderer>();
        cube->start(state);
        cube->renderer->transform.position.y = 0.5f;
    }

    void update(EngineState &state, const Update &time) override
    {
        camera.transform.position = Quat::from_euler({0, time.delta_time * 0.5f, 0}) * camera.transform.position;
        camera.transform.rotation = camera.transform.rotation * Quat::from_euler({0, -time.delta_time * 0.5f, 0});

        ground->update(state, time);
        cube->update(state, time);
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