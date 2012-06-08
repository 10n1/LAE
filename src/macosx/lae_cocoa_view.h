/*
 *  lae_cocoa_view_t.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

#import <Cocoa/Cocoa.h>

struct lae_graphics_t;

@interface lae_cocoa_view_t : NSView

@property struct lae_graphics_t* graphics;

@end
