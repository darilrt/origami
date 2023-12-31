#pragma once

#include <iostream>
#include <sokol_gfx.h>

class Sampler
{
public:
    enum Filter
    {
        Nearest = SG_FILTER_NEAREST,
        Linear = SG_FILTER_LINEAR,
    };

    enum Wrap
    {
        Repeat = SG_WRAP_REPEAT,
        MirroredRepeat = SG_WRAP_MIRRORED_REPEAT,
        ClampToEdge = SG_WRAP_CLAMP_TO_EDGE,
    };

    sg_sampler sampler;

    Sampler(
        Filter min_filter = Linear,
        Filter mag_filter = Linear,
        Filter mipmap_filter = Linear,
        Wrap wrap_u = Repeat,
        Wrap wrap_v = Repeat);

    ~Sampler();
};

class Image
{
public:
    static Image *from_file(const std::string &path);

    static Image *from_memory(const void *data, int width, int height);

    static Image *create_render_target(int width, int height);

    static Image *create_depth_target(int width, int height);

    sg_image image = {0};
};