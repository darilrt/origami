#include <origami/core.hpp>
#include <origami/math.hpp>
#include <origami/graphics.hpp>
#include <origami/window.hpp>

#include "origami/components/sprite.hpp"
#include "origami/components/transform.hpp"

SpriteMaterial::SpriteMaterial()
{
    shader = Shader::from_file(
        "assets/shaders/sprite",
        Shader::Descriptor{
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

sg_range SpriteMaterial::get_vs()
{
    return {&uniforms, sizeof(uniforms)};
}

sg_range SpriteMaterial::get_fs()
{
    return {nullptr, 0};
}

void SpriteMaterial::set_std_uniforms(const Mat4 &view, const Mat4 &projection, const Mat4 &model)
{
    uniforms.view = view;
    uniforms.projection = projection;
    uniforms.model = model;
}

void Sprite::start(EngineState &state)
{
    if (!sprite)
    {
        throw std::runtime_error("Sprite::sampler is nullptr");
    }

    auto &graphics = state.get_resource<GraphicsSystem>();

    entity = graphics.create_entity();
    entity->model = transform.get_matrix();
    entity->mesh = primitive::quad();
    entity->material = new SpriteMaterial();
    entity->material->set_texture(0, sprite->image.get(), sprite->sampler.get());
}

void Sprite::update(EngineState &state, const Update &time)
{
    entity->model = transform.get_matrix();
}

void Sprite::set_visible(bool visible)
{
    entity->is_visible = visible;
}

bool Sprite::is_visible()
{
    return entity->is_visible;
}