/*
 *  core.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_core.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdlib.h>
#include <string.h>
/* External headers */
/* Internal headers */
#include "lae_timer.h"
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
struct lae_core
{
    lae_timer_t main_timer;
};

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
lae_core* lae_core_create(void)
{
    lae_core* core = NULL;
    
    /* Allocate the core */
    core = (lae_core*)malloc(sizeof(*core));
    memset(core, 0, sizeof(*core));
    
    /* Set up subsystems */
    
    /* Get the ball rolling */
    lae_timer_init(&core->main_timer);
    
    return core;
}
void lae_core_destroy(lae_core* core)
{
    /* Shutdown subsystems */
    
    /* Deallocate the core */
    free(core);
}
