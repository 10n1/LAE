 /*
 *  graphics_opengl.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_graphics.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdio.h>
/* External headers */
/* Internal headers */
#include "graphics_opengl.h"
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
void lae_graphics_clear(lae_graphics_t* device)
{
    UNUSED_PARAMETER(device);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CheckGLError();
}
void lae_graphics_clear_color(lae_graphics_t* device, float r, float g, float b, float a, float d)
{
    glClearColor(r,g,b,a);
    CheckGLError();
    glClearDepth(d);
    CheckGLError();
    UNUSED_PARAMETER(device);
}
void lae_graphics_set_depth_test(lae_graphics_t* device, int test, int write)
{
    if((test & write) == 0)
    {
        glDisable(GL_DEPTH_TEST);
    }
    else
        glEnable(GL_DEPTH_TEST);
    
    glDepthMask( write ? GL_TRUE : GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    CheckGLError();
    UNUSED_PARAMETER(device);
}
void lae_graphics_set_alpha_test(lae_graphics_t* device, int enable)
{
    if(enable)
    {
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }
    CheckGLError();
    UNUSED_PARAMETER(device);
}

