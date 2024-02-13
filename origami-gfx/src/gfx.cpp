#include "GL/glew.hpp"
#include <GL/gl.h>
#include <iostream>

#include "origami/gfx.hpp"

namespace gfx
{
    void init()
    {
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Error initializing GLEW" << std::endl;
        }
    }

    void clear_color(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void draw(size_t vertex_count, size_t instance_count, size_t first_vertex, size_t first_instance)
    {
        if (instance_count == 1)
        {
            glDrawArrays(GL_TRIANGLES, first_vertex, vertex_count);
        }
        else
        {
            glDrawArraysInstanced(GL_TRIANGLES, first_vertex, vertex_count, instance_count);
        }
    }

    void set_viewport(float x, float y, float width, float height)
    {
        glViewport(x, y, width, height);
    }

    void enable_depth_test(bool enable)
    {
        if (enable)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void enable_backface_culling(bool enable)
    {
        if (enable)
        {
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }
    }

    void enable_wireframe(bool enable)
    {
        if (enable)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    void enable_blending(bool enable)
    {
        if (enable)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else
        {
            glDisable(GL_BLEND);
        }
    }

    void unbind_framebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

} // namespace gfx