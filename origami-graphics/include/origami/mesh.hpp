#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <vector>
#include <sokol_gfx.h>

class StaticMesh
{
public:
    StaticMesh(std::vector<Vec3> vertices, std::vector<Vec3> normals, std::vector<Vec2> uvs, std::vector<uint32_t> indices);

private:
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    std::vector<uint32_t> indices;

    sg_bindings bindings;
};