#pragma once

#include "origami/graphics/mesh.hpp"

namespace primitive
{

    Mesh *quad();

    Mesh *cube();

    Mesh *sphere(int subdivisions_x = 32, int subdivisions_y = 16);

    Mesh *cylinder(int subdivisions_x = 32);

    Mesh *torus(float radius = 0.5f, float thickness = 0.25f, int subdivisions_x = 32, int subdivisions_y = 16);

    Mesh *plane();

} // namespace primitive
