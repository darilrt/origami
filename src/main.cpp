#include <memory>
#include <iostream>

#include <origami/core.hpp>
#include <origami/window.hpp>
#include <origami/event.hpp>
#include <origami/graphics.hpp>
#include <origami/assets.hpp>

class SimpleMaterial : public Material
{
public:
    struct
    {
        STD_UNIFORM_HEADER_VS
        Vec3 color;
    } uniforms;

    SimpleMaterial()
    {
        shader = Shader::from_file(
            "assets/shaders/default",
            sizeof(uniforms),
            {
                {"view", SG_UNIFORMTYPE_MAT4},
                {"projection", SG_UNIFORMTYPE_MAT4},
                {"model", SG_UNIFORMTYPE_MAT4},
                {"color", SG_UNIFORMTYPE_FLOAT3},
            },
            0, {});
    }

    sg_range get_vs() override
    {
        return {&uniforms, sizeof(uniforms)};
    }

    sg_range get_fs() override
    {
        return {nullptr, 0};
    }

    void set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model) override
    {
        uniforms.view = view;
        uniforms.projection = projection;
        uniforms.model = model;
    }
};

class Game : public Resource
{
public:
    GraphicEntity *entity;

    void init(EngineState &state) override
    {
        auto &es = state.get_resource<EventSystem>();
        es.regist<Start>([&](EngineState &state, void *payload)
                         { this->start(state); });

        es.regist<Update>([&](EngineState &state, void *payload)
                          { this->update(state, *static_cast<Update *>(payload)); });
    }

    void start(EngineState &state)
    {
        auto &window = state.get_resource<Window>();
        window.set_size({1280, 720});
        window.set_title("Origami");
        window.set_vsync(true);

        auto &graphics = state.get_resource<GraphicsSystem>();

        float half_width_x = (window.get_size().x / 2) / 200;
        float half_width_y = (window.get_size().y / 2) / 200;

        graphics.set_view(Mat4::identity());
        graphics.set_projection(Mat4::ortho(-half_width_x, half_width_x, -half_width_y, half_width_y, -1.0f, 1.0f));

        entity = &graphics.create_entity();
        entity->model = Mat4::identity();
        entity->mesh = primitive::quad();
        entity->material = new SimpleMaterial();
        ((SimpleMaterial *)entity->material)->uniforms.color = {1.0f, 0.5f, 0.2f};
    }

    void update(EngineState &state, Update &time)
    {
        entity->model = Quat::from_euler({0.0f, 0.0f, sin(time.life_time)}).to_mat4();
    };
};

int main()
{
    auto state = std::make_unique<EngineState>();
    state->init_resource<AssetManager>();
    state->init_resource<EventSystem>();
    state->init_resource<Window>();
    state->init_resource<GraphicsSystem>();
    state->init_resource<Game>();
    state->start();

    state->get_resource<Window>().run(*state);
    return 0;
}
