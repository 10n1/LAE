/*
 *  graphics_opengl.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_graphics_opengl_h_
#define __lae_graphics_opengl_h_

#include "lae_graphics.h"

/*----------------------------------------------------------------------------*/
/* C headers */
/* C++ headers */
/* External headers */
#if defined(_WIN32)
    #include "gl/glew.h"
    #include "gl/wglew.h"
#elif defined(__APPLE__)
    #include <OpenGL/OpenGL.h>
    #include <opengl/gl3.h>
#endif
/* Internal headers */
#include "lae_config.h"
#include "lae_assert.h"
#include "lae_defines.h"
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" { // Use C linkage
#endif 

/**
 * OpenGL error reporting functions
 */
#define CheckGLError() \
    {\
        GLenum error__ = glGetError(); \
        if(error__ != GL_NO_ERROR) \
            printf("%s\n", GetGLErrorString(error__));\
        assert(error__ == GL_NO_ERROR); \
    }
#define OPENGL_ERROR_STRING(e) case e: return #e;
static const char * GetGLErrorString(GLenum error)
{
    switch( error )
    {
    OPENGL_ERROR_STRING(GL_NO_ERROR);
    OPENGL_ERROR_STRING(GL_INVALID_ENUM);
    OPENGL_ERROR_STRING(GL_INVALID_VALUE);
    OPENGL_ERROR_STRING(GL_INVALID_OPERATION);
    OPENGL_ERROR_STRING(GL_OUT_OF_MEMORY);
    OPENGL_ERROR_STRING(GL_INVALID_FRAMEBUFFER_OPERATION);
#ifdef _gl_h_
    OPENGL_ERROR_STRING(GL_STACK_OVERFLOW);
    OPENGL_ERROR_STRING(GL_STACK_UNDERFLOW);
    OPENGL_ERROR_STRING(GL_TABLE_TOO_LARGE);
#endif
    default:
        return "ERROR: Unknown Error Enum";
    }
}

struct lae_graphics_t
{
#if LAE_PLATFORM_ID == LAE_PLATFORM_MACOS
    void*  context;
    void*  pixel_format;
#elif LAE_PLATFORM_ID == LAE_PLATFORM_WINDOWS
    HDC     dc;
    HGLRC   rc;
#endif
};

#ifdef __cplusplus
}
#endif

#endif /* include guard */
