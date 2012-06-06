/*
 *  lae_scripting.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_scripting_h_
#define __lae_lae_scripting_h_

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdint.h>
/* C++ headers */
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" { // Use C linkage
#endif

/**
 * The struct that holds all the necessary scripting handles
 */
typedef struct lae_scripting_t lae_scripting_t;

/**
 * Allocates and initalizes a scripting interface
 */
lae_scripting_t* lae_scripting_create(void);

/**
 * Tears down the scripting interface and clears the memory
 */
void lae_scripting_destroy(lae_scripting_t* script);

#ifdef __cplusplus
}
#endif

#endif /* include guard */
