/*
 *  resource_manager.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/7/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_resources.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
enum { MAX_RESOURCES = 1024 };

struct lae_resource_manager_t
{
    lae_resource_t  resources[MAX_RESOURCES];
    int             num_loaded_resources;
};

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/

lae_resource_manager_t* lae_resource_manager_create(void)
{
    lae_resource_manager_t* manager = (lae_resource_manager_t*)malloc(sizeof(*manager));
    memset(manager, 0, sizeof(*manager));
    
    return manager;
}

void lae_resource_manager_destroy(lae_resource_manager_t* manager)
{
    free(manager);
}
lae_resource_t* lae_resource_manager_load(  lae_resource_manager_t* manager, 
                                            const char* resource_name)
{
    int ii;
    for(ii=0; ii<manager->num_loaded_resources; ++ii)
    {
        if(strcmp(resource_name, manager->resources[ii].name) == 0)
            return &manager->resources[ii];
    }
    
    /* Isn't already loaded, load it */
    
    return NULL;
}
