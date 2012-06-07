/*
 *  timer.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_timer.h"
#include "lae_config.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#ifdef _WIN32
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach/mach_time.h>
#endif
/* External headers */
/* Internal headers */
#include "lae_scripting.h"
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
#if (LAE_PLATFORM_ID == LAE_PLATFORM_MACOS) || \
    (LAE_PLATFORM_ID == LAE_PLATFORM_IOS)
void lae_timer_init(lae_timer_t* timer)
{
    mach_timebase_info_data_t frequency = {0,0};
    mach_timebase_info(&frequency);
    timer->frequency = (double)frequency.numer / (double)frequency.denom;
    timer->frequency *= 1e-9;
    timer->startTime = timer->prevTime = mach_absolute_time();
}
void lae_timer_reset(lae_timer_t* timer)
{
    timer->startTime = timer->prevTime = mach_absolute_time();
}
double lae_timer_delta_time(lae_timer_t* timer)
{
    uint64_t    current_time    = mach_absolute_time();
    double      delta_time      = (double)(current_time - timer->prevTime) * timer->frequency;
    timer->prevTime = current_time;
    
    return delta_time;
}
double lae_timer_running_time(lae_timer_t* timer)
{
    uint64_t    current_time = mach_absolute_time();
    double      running_time = (double)(current_time - timer->startTime) * timer->frequency;
    
    return running_time;
}
#elif (LAE_PLATFORM_ID == LAE_PLATFORM_WINDOWS)
void lae_timer_init(lae_timer_t* timer)
{
    LARGE_INTEGER   freq;
    QueryPerformanceFrequency( &freq );
    timer->frequency = 1.0/(double)freq.QuadPart;
    
    QueryPerformanceCounter((LARGE_INTEGER*)&timer->startTime);
    timer->prevTime = timer->startTime;
}
void lae_timer_reset(lae_timer_t* timer)
{
    QueryPerformanceCounter((LARGE_INTEGER*)&timer->startTime);
    timer->prevTime = timer->startTime;
}
double lae_timer_delta_time(lae_timer_t* timer)
{  
    uint64_t    current_time;
    double      delta_time;

    QueryPerformanceCounter((LARGE_INTEGER*)&current_time);
    delta_time = (current_time - timer->prevTime) * timer->frequency;
    timer->prevTime = current_time;
    return delta_time;
}
double lae_timer_running_time(lae_timer_t* timer)
{
    uint64_t    current_time;
    double      running_time;

    QueryPerformanceCounter( (LARGE_INTEGER*)&current_time );
    running_time = (current_time - timer->startTime) * timer->frequency;
    return running_time; 
}

#else
    #error Need a timer!
#endif /* platform */

LAE_SCRIPTING_EXPORT_FUNCTION(lae_timer_init)
{
    lae_timer_t* timer = lae_scripting_ptr_from_lua(L, 1);
    lae_timer_init(timer);
    return 0;
}
LAE_SCRIPTING_EXPORT_FUNCTION(lae_timer_reset)
{
    lae_timer_t* timer = lae_scripting_ptr_from_lua(L, 1);
    lae_timer_reset(timer);
    return 0;
}
LAE_SCRIPTING_EXPORT_FUNCTION(lae_timer_delta_time)
{
    lae_timer_t* timer = lae_scripting_ptr_from_lua(L, 1);
    lae_scripting_float_to_lua(L, (float)lae_timer_delta_time(timer));
    return 1;
}
LAE_SCRIPTING_EXPORT_FUNCTION(lae_timer_running_time)
{
    lae_timer_t* timer = lae_scripting_ptr_from_lua(L, 1);
    lae_scripting_float_to_lua(L, (float)lae_timer_delta_time(timer));
    return 1;
}

void lae_timer_export(struct lae_scripting_t* scripting)
{
    static const lae_scripting_function_t timer_functions[] =
    {
        LAE_SCRIPTING_FUNCTION(lae_timer_init),
        LAE_SCRIPTING_FUNCTION(lae_timer_reset),
        LAE_SCRIPTING_FUNCTION(lae_timer_delta_time),
        LAE_SCRIPTING_FUNCTION(lae_timer_running_time),
        { NULL, NULL }
    };
    lae_scripting_export_functions(scripting, timer_functions);
}

