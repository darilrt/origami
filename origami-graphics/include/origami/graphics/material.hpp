#pragma once

#include <origami/graphics/shader.hpp>
#include <sokol_gfx.h>

class Material
{
    friend class GraphicEntity;

public:
private:
    Shader shader;
};