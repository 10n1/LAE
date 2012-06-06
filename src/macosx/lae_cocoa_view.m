/*
 *  lae_cocoa_view.m
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

#import "lae_cocoa_view.h"

@implementation lae_cocoa_view_t

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
                                             selector:@selector(windowResized:) name:NSWindowDidResizeNotification
                                               object:[self window]];
}
- (void)reshape
{
}
- (void)windowResized:(NSNotification *)notification;
{
}

@end
