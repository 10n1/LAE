/*
 *  lae_timer.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_timer_h_
#define __lae_lae_timer_h_

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdint.h>
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

typedef struct
{
    uint64_t    startTime;
    uint64_t    prevTime;
    double      frequency;
} lae_timer_t;

#ifdef __cplusplus
extern "C" { // Use C linkage
#endif 

struct lae_scripting_t;

/**
 * Initializes the timer and its frequency
 */
void lae_timer_init(lae_timer_t* timer);

/**
 * Resets the timer to count from zero
 */
void lae_timer_reset(lae_timer_t* timer);

/**
 * Returns the time that has passed (in seconds)
 * since the last call to lae_timer_delta_time
 */
double lae_timer_delta_time(lae_timer_t* timer);

/**
 * Returns the time in seconds since the last call to init or reset
 */
double lae_timer_running_time(lae_timer_t* timer);

/**
 * Exports the timer functions to the scripting interface
 */
void lae_timer_export(struct lae_scripting_t* scripting);

#ifdef __cplusplus
}
#endif

#endif /* include guard */
