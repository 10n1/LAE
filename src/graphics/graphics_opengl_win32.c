/*
 *  graphics_opengl_win32.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "graphics_opengl.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdlib.h>
#include <stdio.h>
/* External headers */
/* Internal headers */
#include "lae_assert.h"
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
lae_graphics_t* lae_graphics_create(void* window)
{
    lae_graphics_t* device          = NULL;
    HWND            hWnd            = (HWND)window;
    HDC             hDC             = GetDC(hWnd);
    HGLRC           hGLRC           = NULL;
    int             pixel_format    = 0;
    BOOL            success         = 1;
    GLenum          error           = GL_NO_ERROR;
	PIXELFORMATDESCRIPTOR   pfd     = {0};
    const char*             glversion = NULL;

    /* Create context to load extensions */
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize       = sizeof(pfd);
	pfd.nVersion    = 1;
	pfd.dwFlags     = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType  = PFD_TYPE_RGBA;
	pfd.cColorBits  = 32;
	pfd.cDepthBits  = 32;
	pfd.iLayerType  = PFD_MAIN_PLANE;

    pixel_format = ChoosePixelFormat(hDC, &pfd);
    assert(pixel_format != 0);
    success = SetPixelFormat(hDC, pixel_format, &pfd);
    assert(success);

    /* Create context */
    hGLRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hGLRC);
    CheckGLError();

    /* Glew */
    error = glewInit();
    CheckGLError();
    if(GLEW_OK != error)
    {
        /* Glew init failed...not sure what happened */
        printf("Error: %s\n", glewGetErrorString(error));
        assert(0);
    }

    if(wglewIsSupported("WGL_ARB_create_context") == 1)
    {
        GLint pCreationAttributes[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB,  3,
            WGL_CONTEXT_MINOR_VERSION_ARB,  2,
            WGL_CONTEXT_PROFILE_MASK_ARB,   WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            WGL_CONTEXT_FLAGS_ARB,          WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0,
        };
        HGLRC new_context = wglCreateContextAttribsARB(hDC, 0, pCreationAttributes);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hGLRC);
        wglMakeCurrent(hDC, new_context);
        hGLRC = new_context;
    }

    /* Create the device */
    glversion = (const char*)glGetString(GL_VERSION);

    device = (lae_graphics_t*)malloc(sizeof(*device));
    device->dc = hDC;
    device->rc = hGLRC;

    return device;
}
void lae_graphics_destroy(lae_graphics_t* device)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(device->rc);
    free(device);
}
void lae_graphics_present(lae_graphics_t* device)
{
    SwapBuffers(device->dc);
    UNUSED_PARAMETER(device);
}
void lae_graphics_set_current(lae_graphics_t* device)
{
    UNUSED_PARAMETER(device);
}
void lae_graphics_resize(lae_graphics_t* device, int width, int height)
{
    glViewport(0,0,width,height);
    CheckGLError();
    UNUSED_PARAMETER(device);
}
