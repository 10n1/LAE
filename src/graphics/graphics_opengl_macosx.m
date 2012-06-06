/*
 *  graphics_opengl_macosx.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "graphics_opengl.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdlib.h>
#include <Cocoa/Cocoa.h>
#include <OpenGL/OpenGL.h>
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
    lae_graphics_t*         device              = NULL;
    NSWindow*               ns_window           = (NSWindow*)window;
    NSOpenGLContext*        cocoa_context       = NULL;
    NSOpenGLPixelFormat*    cocoa_pixel_format  = NULL;
    NSView*                 view                = [ns_window contentView];
    GLint                   vsync_interval      = 0;
    
    NSOpenGLPixelFormatAttribute attributes[] = 
    {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFANoRecovery,
        NSOpenGLPFADoubleBuffer,   
        NSOpenGLPFAColorSize, (NSOpenGLPixelFormatAttribute)32,
        NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)24,
        (NSOpenGLPixelFormatAttribute)0,
    };
    
    cocoa_pixel_format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
    assert(cocoa_pixel_format);
    cocoa_context = [[NSOpenGLContext alloc] initWithFormat:cocoa_pixel_format 
                                               shareContext:nil];
    assert(cocoa_context);
    
    [cocoa_context setView:view];
    CheckGLError();
    [cocoa_context makeCurrentContext];
    CheckGLError();
    [cocoa_context setValues:&vsync_interval forParameter:NSOpenGLCPSwapInterval];
    CheckGLError();
    
    [view setPostsFrameChangedNotifications:YES];
    
    /* Create the device */
    device = (lae_graphics_t*)malloc(sizeof(*device));
    device->context = cocoa_context;
    device->pixel_format = cocoa_pixel_format;
    
    /* Set up base OpenGL params */
    CheckGLError();
    glFrontFace(GL_CW);
    CheckGLError();
    glCullFace(GL_BACK);
    CheckGLError();
    glEnable(GL_CULL_FACE);
    CheckGLError();
    glClearColor(1.0f, 0.4f, 0.5f, 1.0f);
    CheckGLError();
    
    return device;
}
void lae_graphics_destroy(lae_graphics_t* device)
{
    [(NSOpenGLContext*)device->context setView:nil];
    [(NSOpenGLContext*)device->context dealloc];
    [(NSOpenGLContext*)device->pixel_format dealloc];
    
    free(device);
}
void lae_graphics_present(lae_graphics_t* device)
{
    [(NSOpenGLContext*)device->context flushBuffer];
    CheckGLError();
}
void lae_graphics_set_current(lae_graphics_t* device)
{
    [(NSOpenGLContext*)device->context makeCurrentContext];
}
void lae_graphics_resize(lae_graphics_t* device, int width, int height)
{
    glViewport(0, 0, width, height);
    CheckGLError();
    [(NSOpenGLContext*)device->context update];
}
