/*
 *  lae_config.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_config_h_
#define __lae_lae_config_h_

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
/* C++ headers */
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" { // Use C linkage
#endif 

/**
 * Configuration detection
 */
#if defined( DEBUG ) || defined( _DEBUG )
    #ifndef DEBUG
        #define DEBUG
    #endif
#else
    #ifndef RELEASE
        #define RELEASE
    #endif
#endif

/**
 * Platform detection
 */
#define LAE_PLATFORM_WINDOWS 1
#define LAE_PLATFORM_MACOS   2
#define LAE_PLATFORM_LINUX   3
#define LAE_PLATFORM_IOS     4
#define LAE_PLATFORM_ANDROID 5

#if defined( WIN32 )
    #define LAE_PLATFORM_ID LAE_PLATFORM_WINDOWS
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
#elif defined( __MACH__ )
    #include <TargetConditionals.h>
    #if( TARGET_OS_IPHONE )
        #define LAE_PLATFORM_ID LAE_PLATFORM_IOS
    #else
        #define LAE_PLATFORM_ID LAE_PLATFORM_MACOS
    #endif
#elif defined( __ANDROID__ )
    #define LAE_PLATFORM_ID LAE_PLATFORM_ANDROID
#elif defined( __linux__ )
    #define LAE_PLATFORM_ID LAE_PLATFORM_LINUX
#else
    #error No valid target found
#endif

/**
 * ISA detection
 */
#define LAE_ISA_IA32 1
#define LAE_ISA_ARM  2

#if (LAE_PLATFORM_ID == LAE_PLATFORM_ANDROID) || (LAE_PLATFORM_ID == LAE_PLATFORM_IOS)
    #define ISA_ID ISA_ARM /* TODO: Figure out a better way to detect ISA */
#elif (LAE_PLATFORM_ID == LAE_PLATFORM_MACOS) ||\
      (LAE_PLATFORM_ID == LAE_PLATFORM_WINDOWS) || \
      (LAE_PLATFORM_ID == LAE_PLATFORM_LINUX)
    #define LAE_ISA_ID LAE_ISA_IA32
#endif

/**
 * Architecture detection
 */
#define LAE_ARCH_64BIT 1
#define LAE_ARCH_32BIT 2

#if defined( _M_X64 ) || \
    defined( __LP64__ ) || \
    (defined(TARGET_RT_64_BIT) && ( TARGET_RT_64_BIT == 1 ))
    #define LAE_ARCH_ID LAE_ARCH_64BIT
#else
    #define LAE_ARCH_ID LAE_ARCH_32BIT
#endif

/**
 * System information
 */
#define LAE_SYSTEM_POSIX    1
#define LAE_SYSTEM_WINDOWS  2

#if LAE_PLATFORM_ID == LAE_PLATFORM_MACOS || \
    LAE_PLATFORM_ID == LAE_PLATFORM_LINUX || \
    LAE_PLATFORM_ID == LAE_PLATFORM_IOS   || \
    LAE_PLATFORM_ID == LAE_PLATFORM_ANDROID
    #define LAE_SYSTEM_TYPE LAE_SYSTEM_POSIX
#elif LAE_PLATFORM_ID == LAE_PLATFORM_WINDOWS
    #define LAE_SYSTEM_TYPE LAE_SYSTEM_WINDOWS
#else
    #error Unsupported system
#endif

/**
 * Debug information
 */
#if LAE_PLATFORM_ID == LAE_PLATFORM_WINDOWS
    static const char LAE_PLATFORM_NAME[] = "Microsoft Windows";
#elif LAE_PLATFORM_ID == LAE_PLATFORM_IOS
    static const char LAE_PLATFORM_NAME[] = "Apple iOS";
#elif LAE_PLATFORM_ID == LAE_PLATFORM_MACOS
    static const char LAE_PLATFORM_NAME[] = "Apple Mac OS X";
#elif LAE_PLATFORM_ID == LAE_PLATFORM_ANDROID
    static const char LAE_PLATFORM_NAME[] = "Google Android";
#elif LAE_PLATFORM_ID == LAE_PLATFORM_LINUX
    static const char LAE_PLATFORM_NAME[] = "Linux";
#endif

#if LAE_ISA_ID == LAE_ISA_IA32
    static const char LAE_ISA_NAME[] = "Intel x86";
#elif LAE_ISA_ID == LAE_ISA_ARM
    static const char LAE_ISA_NAME[] = "ARM";
#endif

#if LAE_ARCH_ID == LAE_ARCH_64BIT
    static const char LAE_ARCH_NAME[] = "64-bit";
#elif LAE_ARCH_ID == LAE_ARCH_32BIT
    static const char LAE_ARCH_NAME[] = "32-bit";
#endif

/*
 * Helpful macros
 */
#ifndef UNUSED_PARAMETER
    #define UNUSED_PARAMETER(p) (void)(sizeof(p))
#endif

#ifndef ARRAY_LENGTH
    #define ARRAY_LENGTH(a) (sizeof(a)/sizeof(a[0]))
#endif


#ifdef __cplusplus
}
#endif

#endif /* include guard */
