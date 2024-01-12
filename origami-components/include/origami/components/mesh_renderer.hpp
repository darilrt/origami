#pragma once

#include <origami/graphics.hpp>
#include <origami/window.hpp>
#include "origami/components/transform.hpp"

class MeshRenderer
{
public:
    Transform transform;
    Shared<GraphicEntity> entity;

    void start(EngineState &state);

    void update(EngineState &state, const Update &time);

    inline Shared<Mesh> get_mesh() const { return entity->mesh; }

    inline Shared<Material> get_material() const { return entity->material; }

    inline void set_mesh(Shared<Mesh> mesh) { entity->mesh = mesh; }

    inline void set_material(Shared<Material> material) { entity->material = material; }
};
