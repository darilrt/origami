#include <origami.hpp>

class UIBoxMaterial : public Material
{
public:
    struct
    {
        STD_UNIFORM_HEADER_VS
    } uniforms;
    struct
    {
        Vec4 color;
    } params;

    UIBoxMaterial();

    sg_range get_vs() override;

    sg_range get_fs() override;

    void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) override;
};

UIBoxMaterial::UIBoxMaterial()
{
    shader = Shader::from_file(
        "assets/shaders/sprite",
        Shader::Descriptor{
            .primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP,
            .uniforms_vs = {
                .size = sizeof(uniforms),
                .uniforms = {
                    {"view", SG_UNIFORMTYPE_MAT4},
                    {"projection", SG_UNIFORMTYPE_MAT4},
                    {"model", SG_UNIFORMTYPE_MAT4},
                },
            },
            .images = {
                {"sprite", SG_IMAGETYPE_2D},
            },
        });
}

sg_range UIBoxMaterial::get_vs()
{
    return {&uniforms, sizeof(uniforms)};
}

sg_range UIBoxMaterial::get_fs()
{
    return {nullptr, 0};
}

void UIBoxMaterial::set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model)
{
    uniforms.view = view;
    uniforms.projection = projection;
    uniforms.model = model;
}

class UIBox
{
public:
    Vec2 position;
    Vec2 size = {1.0, 1.0};
    Vec4 color = {1.0, 1.0, 1.0, 1.0};

    Shared<UIBoxMaterial> material = new_shared<UIBoxMaterial>();
    Shared<MeshRenderer> mesh_renderer = new_shared<MeshRenderer>();

    void start(EngineState &state)
    {
        auto &graphics = state.get_resource<GraphicsSystem>();

        mesh_renderer->start(state);
        mesh_renderer->set_mesh(Shared<Mesh>(primitive::quad()));
        mesh_renderer->set_material(material);
    }

    void update(EngineState &state, const Update &time)
    {
        mesh_renderer->transform.position = {position.x, position.y, 0.0};
        mesh_renderer->transform.scale = {size.x, size.y, 1.0};
    }
};

class Player : public Entity
{
public:
    Transform transform;
    Camera camera;

    Unique<UIBox> box = new_unique<UIBox>();

    void start(EngineState &state) override
    {
        auto &window = state.get_resource<Window>();

        camera.start(state);
        camera.set_active(state);
        camera.set_orthographic(1.0, -100.0, 100.0);
        camera.set_resolution(window.get_size());

        auto &assets = state.get_resource<AssetManager>();

        box->start(state);
        box->material->set_texture(0, assets.get<Texture>("assets/textures/SandyStoneRoad/SandyStoneRoad01_BaseColor.png"));
    }

    void update(EngineState &state, const Update &time) override
    {
        box->update(state, time);
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