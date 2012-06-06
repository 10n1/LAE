/*
 *  lae_graphics.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_graphics_h_
#define __lae_lae_graphics_h_

/*----------------------------------------------------------------------------*/
/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" { // Use C linkage
#endif

typedef struct lae_graphics_t lae_graphics_t;

/**
 * Creates and initializes the graphics device
 * @param window Pointer to the platform-specific window
 *      (NSWindow* in OS X, HWND in Windows)
 */
lae_graphics_t* lae_graphics_create(void* window);

/**
 * Destroys the graphics device
 */
void lae_graphics_destroy(lae_graphics_t* device);

/**
 * Clears the current render and depth target
 */
void lae_graphics_clear(lae_graphics_t* device);

/**
 * Flips the back buffer
 */
void lae_graphics_present(lae_graphics_t* device);

/**
 * Make the current device the active one
 */
void lae_graphics_set_current(lae_graphics_t* device);

/**
 * Sets the new size of the back buffer
 */
void lae_graphics_resize(lae_graphics_t* device, int width, int height);

/**
 * Pipeline management
 */
void lae_graphics_clear_color(lae_graphics_t* device, float r, float g, float b, float a, float d);
void lae_graphics_set_depth_test(lae_graphics_t* device, int test, int write);
void lae_graphics_set_alpha_test(lae_graphics_t* device, int enable);

#ifdef __cplusplus
}
#endif

#endif /* include guard */
