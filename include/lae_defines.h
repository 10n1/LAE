/*
 *  lae_defines.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_defines_h_
#define __lae_lae_defines_h_

/**
 * Helpful macros
 */
#ifndef UNUSED_PARAMETER
    #define UNUSED_PARAMETER(param) (void)(param)
#endif

#ifndef ARRAY_LENGTH
    #define ARRAY_LENGTH(a) (sizeof(a)/sizeof(a[0]))
#endif

/**
 * bool in C
 */
#ifndef __cplusplus
    #if __STDC_VERSION__ >= 199901L
        #include <stdbool.h>
    #elif !defined(bool)
        typedef enum bool
        {
            false = 0, 
            true = 1
        } bool;
    #endif
#endif

/**
 * Alignment
 */
#if defined(_MSC_VER)
    #define ALIGN_STRUCT(x) __declspec(align(x))
#elif defined(__GNUC__)
    #define ALIGN_STRUCT(x) __attribute__ ((aligned(x)))
#else
    #error Need to add alignment support
#endif


#ifdef __cplusplus

/**
 * C++ is_pointer
 */
template <class T>
struct is_pointer
{
    enum {value = false};
};

template <class T>
struct is_pointer<T*>
{
    enum {value = true};
};

template <class T>
struct is_pointer<const T*>
{
    enum {value = true};
};

#endif

#endif /* include guard */
