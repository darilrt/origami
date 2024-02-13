#include "origami/components/mesh_renderer.hpp"

void MeshRenderer::start(EngineState &state)
{
    auto &graphics = state.get_resource<GraphicsSystem>();
    entity = graphics.create_entity();

    if (!entity->mesh)
        entity->mesh = Shared<Mesh>(new Mesh({}));

    if (!entity->material)
        entity->material = new_shared<Material>();

    entity->model = transform.get_matrix();
}

void MeshRenderer::update(EngineState &state, const Update &time)
{
    entity->model = transform.get_matrix();
}