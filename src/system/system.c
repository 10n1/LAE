/*
 *  system.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_system.h"
#include "lae_config.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#if LAE_PLATFORM_ID == LAE_PLATFORM_MACOS
    #include <sys/types.h>
    #include <sys/sysctl.h>
#elif LAE_PLATFORM_ID == LAE_PLATFORM_WINDOWS
    #include <Windows.h>
#endif
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
uint64_t lae_system_get_total_memory(void)
{
#if LAE_PLATFORM_ID == LAE_PLATFORM_MACOS
    uint64_t    memory = 0;
    int         mib[] = {CTL_HW, HW_MEMSIZE};
    size_t      length = sizeof(memory);
    
    sysctl(mib, 2, &memory, &length, NULL, (size_t)0);
    return memory;
#else
    #error Implement for this system
    return 0;
#endif
}
int lae_system_get_cache_line_width(void)
{
#if LAE_PLATFORM_ID == LAE_PLATFORM_MACOS
    size_t line_size = 0;
    size_t sizeof_line_size = sizeof(line_size);

    sysctlbyname("hw.cachelinesize", &line_size, &sizeof_line_size, 0, (size_t)0);

    return (int)line_size;
#else
    #error Implement for this system
    return 0;
#endif
}

int lae_system_get_num_hardware_threads(void)
{
#if LAE_PLATFORM_ID == LAE_PLATFORM_MACOS
    int     num_hardware_threads = -1;
    int     mib[] = { CTL_HW, HW_AVAILCPU }; /* Interested in availible CPUs */
    size_t  length = sizeof(num_hardware_threads);
    
    /* Reads system info */
    sysctl(mib, (uint)ARRAY_LENGTH(mib), &num_hardware_threads, &length, NULL, (size_t)0);
    
    if(num_hardware_threads < 1) 
    {   /* HW_AVAILCPU might have been the problem, try HW_NCPU */
        mib[1] = HW_NCPU;
        sysctl(mib, (uint)ARRAY_LENGTH(mib), &num_hardware_threads, &length, NULL, (size_t)0);
    }
    return num_hardware_threads;
#else
    #error Implement for this system
    return 0;
#endif
}
