#include "origami/graphics/sampler.hpp"

Sampler::Sampler(
    Filter min_filter,
    Filter mag_filter,
    Filter mipmap_filter,
    Wrap wrap_u,
    Wrap wrap_v,
    CompareFunc compare_func)
{
    sampler = sg_make_sampler(sg_sampler_desc{
        .min_filter = (sg_filter)min_filter,
        .mag_filter = (sg_filter)mag_filter,
        .mipmap_filter = (sg_filter)mipmap_filter,
        .wrap_u = (sg_wrap)wrap_u,
        .wrap_v = (sg_wrap)wrap_v,
        .compare = (sg_compare_func)compare_func,
    });
}

Sampler::~Sampler()
{
    sg_destroy_sampler(sampler);
}
