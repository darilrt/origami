#pragma once

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

    enum CompareFunc
    {
        Default = _SG_COMPAREFUNC_DEFAULT,
        Never = SG_COMPAREFUNC_NEVER,
        Less = SG_COMPAREFUNC_LESS,
        Equal = SG_COMPAREFUNC_EQUAL,
        LessEqual = SG_COMPAREFUNC_LESS_EQUAL,
        Greater = SG_COMPAREFUNC_GREATER,
        NotEqual = SG_COMPAREFUNC_NOT_EQUAL,
        GreaterEqual = SG_COMPAREFUNC_GREATER_EQUAL,
        Always = SG_COMPAREFUNC_ALWAYS,
    };

    sg_sampler sampler;

    Sampler(
        Filter min_filter = Linear,
        Filter mag_filter = Linear,
        Filter mipmap_filter = Linear,
        Wrap wrap_u = Repeat,
        Wrap wrap_v = Repeat,
        CompareFunc compare_func = Default);

    ~Sampler();
};
