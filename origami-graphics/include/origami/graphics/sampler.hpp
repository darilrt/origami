#pragma once

class Sampler
{
public:
    enum Filter
    {
        Nearest,
        Linear,
    };

    enum Wrap
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
    };

    enum CompareFunc
    {
        Default,
        Never,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always,
    };

    Sampler(
        Filter min_filter = Linear,
        Filter mag_filter = Linear,
        Filter mipmap_filter = Linear,
        Wrap wrap_u = Repeat,
        Wrap wrap_v = Repeat,
        CompareFunc compare_func = Default);

    ~Sampler();
};
