#pragma once

#include <origami/core.hpp>

using glid_t = uint32_t;

void CheckOpenGLError(const char *stmt, const char *fname, int line);

#ifdef _DEBUG
#define GL_CALL(stmt)                                \
    do                                               \
    {                                                \
        stmt;                                        \
        CheckOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)
#else
#define GL_CALL(stmt) stmt
#endif