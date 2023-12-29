#include <origami.hpp>
#include <memory>
#include <iostream>

#include "simple_material.hpp"
#include "transform.hpp"

class Sprite
{
public:
    std::shared_ptr<Sampler> sampler;
    Transform transform;
    GraphicEntity *entity;

    void start(EngineState &state)
    {
        if (!sampler)
        {
            throw std::runtime_error("Sprite::sampler is nullptr");
        }

        auto &graphics = state.get_resource<GraphicsSystem>();

        entity = &graphics.create_entity();
        entity->mesh = primitive::quad();
        entity->material = new SimpleMaterial();
        entity->material->set_texture(0, sampler.get());
        entity->model = transform.get_matrix();
    }

    void update(EngineState &state, const Update &time)
    {
        entity->model = transform.get_matrix();
    }

    void set_visible(bool visible)
    {
        entity->is_visible = visible;
    }

    bool is_visible()
    {
        return entity->is_visible;
    }
};

class Player : public Entity
{
public:
    Sprite sprite;
    Transform transform;

    void start(EngineState &state) override
    {
        sprite.sampler = std::shared_ptr<Sampler>(Sampler::from_file("assets/textures/mint.png"));
        sprite.transform.parent = &transform;
        sprite.transform.position = {0.5f, 0.5f, 0.0f};
        sprite.start(state);
    }

    void update(EngineState &state, const Update &time) override
    {
        static auto &input = state.get_resource<Input>();

        if (input.key_down(KeyCode::T))
        {
            sprite.set_visible(!sprite.is_visible());
        }

        transform.rotation *= Quat::from_euler({0.0f, 0.0f, time.delta_time});

        sprite.update(state, time);
    }

    void destroy(EngineState &state) override {}
};

class Game : public Scene
{
public:
    GraphicEntity *entity;

    void start(EngineState &state) override
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