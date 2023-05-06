#ifndef MACROS_H
#define MACROS_H

#include <GL/glew.h>
#include <iostream>

#ifdef _MSC_VER
    #define GL_DEBUG_BREAK __debugbreak()
#elif defined(__GNUC__)
    #define GL_DEBUG_BREAK __builtin_trap()
#else
    #error "GL_DEBUG_BREAK not defined for this platform"
#endif

#define GLCall(x) \
    GLClearError(); \
    x; \
    if (GLLogCall(#x, __FILE__, __LINE__)) GL_DEBUG_BREAK

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif
