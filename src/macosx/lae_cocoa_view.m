  /*
 *  lae_cocoa_view.m
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

#import "lae_cocoa_view.h"
#include "lae_graphics.h"

@implementation lae_cocoa_view_t

@synthesize graphics;

- (BOOL)isOpaque
{
    return YES;
}
- (BOOL)canBecomeKeyView
{
    return YES;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}
-(void) viewDidMoveToWindow
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(windowResized:) 
                                                 name:NSWindowDidResizeNotification
                                               object:[self window]];
}
- (void)reshape
{
    if(graphics)
        lae_graphics_resize(graphics, (int)[self bounds].size.width, (int)[self bounds].size.height);
}
- (void)windowResized:(NSNotification *)notification;
{    
    if(graphics)
        lae_graphics_resize(graphics, (int)[self bounds].size.width, (int)[self bounds].size.height);
}

@end
