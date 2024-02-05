#include <origami/core.hpp>
#include <origami/math.hpp>
#include <origami/graphics.hpp>
#include <origami/window.hpp>

#include "origami/components/sprite.hpp"
#include "origami/components/transform.hpp"

void Sprite::start(EngineState &state)
{
    if (!sprite)
    {
        throw std::runtime_error("Sprite::sampler is nullptr");
    }

    auto &graphics = state.get_resource<GraphicsSystem>();

    entity = graphics.create_entity();
    entity->model = transform.get_matrix();
    entity->mesh = Shared<Mesh>(primitive::quad());
    entity->material = new_shared<SpriteMaterial>();
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