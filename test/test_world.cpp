/*
 *  test_world.cpp
 *  lae
 *
 *  Created by Kyle C Weicht on 6/13/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

/*----------------------------------------------------------------------------*/
/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */
#include "lae_test.h"
#include "lae_world.h"
/*----------------------------------------------------------------------------*/

namespace
{
/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
TEST(CreateWorld)
{
    lae_world_t* world = lae_world_create();
    CHECK_POINTER_NOT_NULL(world);
    CHECK_EQUAL(0, lae_world_num_active_entities(world));
    lae_world_destroy(world);
}
TEST(CreateEntity)
{
    lae_world_t* world = lae_world_create();
    int num_entities = lae_world_num_active_entities(world);
    CHECK_EQUAL(0, num_entities);
    
    lae_entity_t* entity = lae_world_spawn_entity(world);
    CHECK_POINTER_NOT_NULL(entity);
    num_entities = lae_world_num_active_entities(world);
    CHECK_EQUAL(1, num_entities);
    lae_world_destroy_entity(world, entity);
    num_entities = lae_world_num_active_entities(world);
    CHECK_EQUAL(0, num_entities);
    lae_world_destroy(world);
}

} // anonymous namespace

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
