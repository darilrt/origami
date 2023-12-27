#include <memory>
#include <iostream>

#include <origami/core.hpp>
#include <origami/window.hpp>
#include <origami/event.hpp>
#include <origami/graphics.hpp>
#include <origami/assets.hpp>

class Game : public Resource
{
public:
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

        auto shader = Shader();
        auto material = std::make_shared<Material>(shader);
        auto mesh = Mesh({
                             {0.0f, 0.5f, 0.0f},
                             {-0.5f, -0.5f, 0.0f},
                             {0.5f, -0.5f, 0.0f},
                         },
                         {
                             {0.0f, 0.0f, 1.0f},
                             {0.0f, 0.0f, 1.0f},
                             {0.0f, 0.0f, 1.0f},
                         },
                         {
                             {0.0f, 0.0f},
                             {0.0f, 1.0f},
                             {1.0f, 1.0f},
                         },
                         {
                             0,
                             1,
                             2,
                         });

        auto &entity = graphics.create_entity();
        entity.set_material(material);
        entity.set_mesh(std::make_shared<Mesh>(mesh));

        // auto texture = Texture::from_file("assets/texture.png");
        // auto shader = Shader::from_file("assets/shader.glsl");
        // auto mesh = Mesh::from_file("assets/mesh.obj");

        // auto material = Material::create(shader);
        // material->set_texture("u_texture", texture);

        // auto entity = Entity::create();
        // entity->set_mesh(mesh);
        // entity->set_material(material);

        // graphics.add_entity(entity);
    }

    void update(EngineState &state, Update &time)
    {
        std::cout << "FPS: " << (1.0f / time.delta_time) << std::endl;
    }
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
