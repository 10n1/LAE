/*
 *  AppDelegate.h
 *  lae_osx
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

#import <Cocoa/Cocoa.h>
#import <CoreVideo/CoreVideo.h>

struct lae_graphics_t;

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property struct lae_graphics_t* graphics;
@property CVDisplayLinkRef display_link;

@end
