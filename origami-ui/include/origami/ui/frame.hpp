#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <origami/graphics.hpp>

class WidgetDraw
{
public:
    Mesh mesh;
    Material material;
};

class Widget
{
public:
    virtual void draw() = 0;
};

class Frame
{
public:
    std::vector<Widget> children;

    void bake();
};