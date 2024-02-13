#include <GL/gl.h>

#include "origami/gfx/gfx_defs.hpp"

void CheckOpenGLError(const char *stmt, const char *fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);

#ifndef _DEBUG
        abort();
#endif // _DEBUG
    }
}