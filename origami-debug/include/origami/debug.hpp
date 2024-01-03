#pragma once

#include <origami/core.hpp>
#include <origami/graphics.hpp>
#include <origami/window.hpp>
#include <vector>

class Debug : public Resource
{
public:
    struct ColoredVertex
    {
        Vec3 position;
        Vec4 color;
    };

    void init(EngineState &state) override;

    void draw_line(const Vec3 &start, const Vec3 &end, const Vec4 &color = {1, 1, 1, 1});

private:
    std::vector<ColoredVertex> vertices;

    Shared<Mesh> mesh;
    Shared<GraphicEntity> entity;
};