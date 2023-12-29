#pragma once

#include <iostream>
#include <sokol_gfx.h>

class Sampler
{
public:
    static Sampler *from_file(const std::string &path);

    sg_image image;
    sg_sampler sampler;
};
