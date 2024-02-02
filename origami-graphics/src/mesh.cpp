#include <vulkan/vulkan.h>
#include <stdexcept>

#include "origami/graphics/graphics_system.hpp"
#include "origami/graphics/mesh.hpp"

Mesh::Mesh(Type type)
{
    this->type = type;
}

Mesh::Mesh(const std::vector<Vertex> &vertices, Type type)
{
    this->type = type;
    set_vertices(vertices);
}

Mesh::~Mesh()
{
    buffer.destroy();
}

void Mesh::set_vertices(const std::vector<Vertex> &vertices)
{
    if (buffer.id == 0)
    {
        buffer = Buffer::create({
            .device = GraphicsSystem::vk_device,
            .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            .memory_properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            .size = sizeof(Vertex) * vertices.size(),
            .data = (void *)vertices.data(),
        });
    }
    else
    {
        throw std::runtime_error("Mesh already has vertices TODO update buffer");
    }
}
