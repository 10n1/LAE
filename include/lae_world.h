/*
 *  lae_world.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/13/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_world_h_
#define __lae_lae_world_h_

/*----------------------------------------------------------------------------*/
/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" { // Use C linkage
#endif 

typedef struct lae_world_t lae_world_t;
typedef struct lae_entity_t lae_entity_t;

/**
 * Create a game world
 */
lae_world_t* lae_world_create(void);

/**
 * Destory a game world
 */
void lae_world_destroy(lae_world_t* world);

/**
 * Returns the number of active entities in this world
 */
int lae_world_num_active_entities(const lae_world_t* world);

/**
 * Spawns an entity at the origin
 */
lae_entity_t* lae_world_spawn_entity(lae_world_t* world);

/**
 * Destroys a given entity
 */
void lae_world_destroy_entity(lae_world_t* world, lae_entity_t* entity);

#ifdef __cplusplus
}
#endif

#endif /* include guard */
