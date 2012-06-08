/*
 *  lae_resources.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/7/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_resources_h_
#define __lae_lae_resources_h_

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

typedef struct lae_resource_manager_t lae_resource_manager_t;

typedef struct
{
    const char* name;
    union
    {
        void*       ptr;
        intptr_t    i;
    } data;
} lae_resource_t;


/**
 * Creates and initializes a resource manager
 */
lae_resource_manager_t* lae_resource_manager_create(void);

/**
 * Destroys a resource manager
 */
void lae_resource_manager_destroy(lae_resource_manager_t* manager);

/**
 * Loads or returns an already loaded resource
 */
lae_resource_t* lae_resource_manager_load(  lae_resource_manager_t* manager, 
                                            const char* resource_name);

#ifdef __cplusplus
}
#endif

#endif /* include guard */
