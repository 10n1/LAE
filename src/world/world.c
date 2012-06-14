/*
 *  world.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/13/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_world.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdlib.h>
#include <string.h>
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
enum { MAX_ENTITIES = 1024*64 };
struct lae_entity_t
{
    int id;
};
struct lae_world_t
{
    lae_entity_t*   entities[MAX_ENTITIES];
    int             num_active_entities;
    int             entity_id;
};

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
lae_world_t* lae_world_create(void)
{
    lae_world_t* world = NULL;
    
    world = (lae_world_t*)malloc(sizeof(*world));
    memset(world, 0, sizeof(*world));
    world->num_active_entities = 0;
    
    return world;
}
void lae_world_destroy(lae_world_t* world)
{
    free(world);
}
int lae_world_num_active_entities(const lae_world_t* world)
{
    return world->num_active_entities;
}
lae_entity_t* lae_world_spawn_entity(lae_world_t* world)
{
    lae_entity_t* entity = (lae_entity_t*)malloc(sizeof(*entity));
    int entity_index = world->num_active_entities;
    if(entity_index >= MAX_ENTITIES)
        return NULL;
        
    world->num_active_entities++;
    memset(entity, 0, sizeof(*entity));
    entity->id = world->entity_id++;
    world->entities[entity_index] = entity;
    
    return entity;
}
void lae_world_destroy_entity(lae_world_t* world, lae_entity_t* entity)
{
    int ii;
    for(ii=0; ii<world->num_active_entities; ++ii)
    {
        if(world->entities[ii] == entity)
            break;
    }
    for(;ii<world->num_active_entities; ++ii)
    {
        world->entities[ii] = world->entities[ii+1];
    }
    free(entity);
    world->num_active_entities--;
}
