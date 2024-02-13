#pragma once

#include <origami/core.hpp>

#include "origami/gfx/gfx_defs.hpp"
#include "origami/gfx/buffer.hpp"
#include "origami/gfx/vertex_array.hpp"
#include "origami/gfx/shader_module.hpp"
#include "origami/gfx/framebuffer.hpp"

namespace gfx
{
    void init();

    void clear_color(float r, float g, float b, float a);

    void clear();

    void draw(size_t vertex_count, size_t instance_count = 1, size_t first_vertex = 0, size_t first_instance = 0);

    void set_viewport(float x, float y, float width, float height);

    void enable_depth_test(bool enable);

    void enable_backface_culling(bool enable);

    void enable_wireframe(bool enable);

    void enable_blending(bool enable);

    void unbind_framebuffer();
} // namespace gfx
