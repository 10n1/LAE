/*
 *  test_system.cpp
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

/*----------------------------------------------------------------------------*/
/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */
#include "lae_test.h"
#include "lae_system.h"
/*----------------------------------------------------------------------------*/

namespace
{
/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
TEST(GetSystemInfo)
{
    uint64_t system_memory = lae_system_get_total_memory();
    CHECK_GREATER_THAN(system_memory, 1*GIGABYTE);
    
    int cache_line_width = lae_system_get_cache_line_width();
    CHECK_GREATER_THAN(cache_line_width, 32);
    
    int num_hardware_threads = lae_system_get_num_hardware_threads();
    CHECK_GREATER_THAN(num_hardware_threads, 4);
}

} // anonymous namespace

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
