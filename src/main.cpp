#include <origami.hpp>

class PBRRenderer
{
public:
    Shared<LitMaterial> material = new_shared<LitMaterial>();
    Shared<MeshRenderer> renderer = new_shared<MeshRenderer>();

    void start(EngineState &state)
    {
        auto &assets = state.get_resource<AssetManager>();
        material->set_texture(0, assets.get<Texture>("assets/textures/gridbox.png"));

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
        camera.transform.position = {0, 2, 2};
        camera.transform.rotation = Quat::from_euler({math::rad(45.0f), 0, 0});

        ground = new_unique<PBRRenderer>();
        ground->start(state);
        ground->renderer->set_mesh(Shared<Mesh>(primitive::plane()));
        ground->renderer->transform.scale = {10, 10, 10};

        auto &assets = state.get_resource<AssetManager>();
        ground->material->set_texture(0, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_BaseColor.png"));
        ground->material->set_texture(1, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_Normal.png"));
        ground->material->set_texture(2, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_AO.png"));
        ground->material->set_texture(3, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_Roughness.png"));
        ground->material->set_texture(4, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_Roughness.png"));
        ground->material->set_texture(5, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_Metallic.png"));

        cube = new_unique<PBRRenderer>();
        cube->start(state);
        cube->renderer->transform.position.y = 0.5f;
        cube->material->set_texture(0, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_BaseColor.png"));
        cube->material->set_texture(1, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_Normal.png"));
        cube->material->set_texture(2, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_AO.png"));
        cube->material->set_texture(3, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_Roughness.png"));
        cube->material->set_texture(4, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_Roughness.png"));
        cube->material->set_texture(5, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_Metallic.png"));
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