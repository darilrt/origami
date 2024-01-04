#include <iostream>

#include <origami/event.hpp>

#include "origami/debug/line_material.hpp"
#include "origami/debug.hpp"

void Debug::init(EngineState &state)
{
    auto &es = state.get_resource<EventSystem>();

    es.regist<Start>(
        [&](const EngineState &s, void *_)
        {
            auto &graphics = state.get_resource<GraphicsSystem>();
            entity = graphics.create_entity();

            mesh = Shared<Mesh>(new Mesh(Mesh::Dynamic));
            mesh->buffers.push_back(
                new_shared<Buffer>(Buffer::Vertex, Buffer::Dynamic));

            entity->mesh = mesh;
            entity->material = new_shared<LineMaterial>();
            entity->model = Mat4::identity();
        });

    es.regist<PostUpdate>(
        [&](const EngineState &s, void *_)
        {
            if (vertices.empty())
            {
                mesh->vertices_count = 0;
                return;
            }

            mesh->buffers[0]->set_data(vertices.data(), vertices.size() * sizeof(ColoredVertex));
            mesh->vertices_count = vertices.size();
            vertices.clear();
        });
}

void Debug::draw_line(const Vec3 &start, const Vec3 &end, const Vec4 &color)
{
    vertices.push_back({start, color});
    vertices.push_back({end, color});
}