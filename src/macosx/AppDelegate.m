/*
 * AppDelegate.m
 * lae_osx
 *
 * Created by Kyle C Weicht on 6/6/12.
 * Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

#import "AppDelegate.h"
#import "lae_cocoa_view.h"
#include "lae_graphics.h"
#include "lae_assert.h"

typedef struct
{
    NSOpenGLContext* context;
    NSOpenGLPixelFormat* pixel_format;
} temp;

static CVReturn display_link_callback(  CVDisplayLinkRef displayLink, 
                                        const CVTimeStamp* now, 
                                        const CVTimeStamp* outputTime, 
                                        CVOptionFlags flagsIn, 
                                        CVOptionFlags* flagsOut, 
                                        void* displayLinkContext);

@implementation AppDelegate

@synthesize window = _window;
@synthesize graphics;
@synthesize display_link;

- (void)dealloc
{
    CVDisplayLinkStop(display_link);
    CVDisplayLinkRelease(display_link);
    lae_graphics_destroy(graphics);
    [super dealloc];
}
- (void)frame
{
    lae_graphics_set_current(graphics); /*  This only needs to be called once
                                            TODO: Figure out the "right" way to do this */
    lae_graphics_present(graphics);
    lae_graphics_clear(graphics);
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    CGLContextObj       cgl_context         = NULL;
    CGLPixelFormatObj   cgl_pixel_format    = NULL;
    NSView*             view                = NULL;

    /* Insert code here to initialize your application */
    view = [[lae_cocoa_view_t alloc] init];
    [_window setContentView:view];
    [view release];
    
    graphics = lae_graphics_create(_window);
    
    /* Set up display link */
    CVDisplayLinkCreateWithActiveCGDisplays(&display_link);
    CVDisplayLinkSetOutputCallback(display_link, &display_link_callback, self);
    cgl_context = [((temp*)graphics)->context CGLContextObj];
    cgl_pixel_format = [((temp*)graphics)->pixel_format CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(display_link, cgl_context, cgl_pixel_format);
    CVDisplayLinkStart(display_link);
    lae_graphics_set_current(graphics);
}

@end

static CVReturn display_link_callback(  CVDisplayLinkRef displayLink, 
                                        const CVTimeStamp* now, 
                                        const CVTimeStamp* outputTime, 
                                        CVOptionFlags flagsIn, 
                                        CVOptionFlags* flagsOut, 
                                        void* displayLinkContext)
{
    [(AppDelegate*)displayLinkContext frame];
    return 0;
}
