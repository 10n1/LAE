/*
 *  lae_system.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_system_h_
#define __lae_lae_system_h_

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

enum
{
    KILOBYTE = 1024,
    MEGABYTE = 1024*1024,
    GIGABYTE = 1024*1024*1024
};

/**
 * Returns the total amount of system memory in bytes
 */
uint64_t lae_system_get_total_memory(void);

/**
 * Returns cache line width in bytes
 */
int lae_system_get_cache_line_width(void);

/**
 * Returns the number of hardware threads
 * Count's hyper threaded threads as hardware (each core has 2 threads)
 */
int lae_system_get_num_hardware_threads(void);

#ifdef __cplusplus
}
#endif

#endif /* include guard */
