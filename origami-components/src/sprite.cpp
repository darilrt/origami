#include <origami/core.hpp>
#include <origami/math.hpp>
#include <origami/graphics.hpp>
#include <origami/window.hpp>

#include "origami/components/sprite.hpp"
#include "origami/components/transform.hpp"

void Sprite::start(EngineState &state)
{
    auto &graphics = state.get_resource<GraphicsSystem>();
    auto &assets = state.get_resource<AssetManager>();

    entity = graphics.create_entity();
    entity->model = transform.get_matrix();
    entity->mesh = Shared<Mesh>(primitive::quad());
    entity->material = assets.get<Material>("built-in/material/sprite");
}

void Sprite::update(EngineState &state, const Update &time)
{
    if (attached_to_pixel)
    {
        transform.position = {
            std::round(transform.position.x),
            std::round(transform.position.y)};
    }
    entity->model = transform.get_matrix();
}

void Sprite::set_visible(bool visible)
{
    entity->enabled = visible;
}

bool Sprite::is_visible()
{
    return entity->enabled;
}