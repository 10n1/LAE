/*
 *  lae_core.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_core_h_
#define __lae_lae_core_h_

/*----------------------------------------------------------------------------*/
/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" { // Use C linkage
#endif

typedef struct lae_core lae_core;

/**
 * Creates the main engine core
 */
lae_core* lae_core_create(void);

/**
 * Destroys the core
 */
void lae_core_destroy(lae_core* core);

#ifdef __cplusplus
}
#endif

#endif /* include guard */
