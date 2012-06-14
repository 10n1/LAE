/*
 *  test_resource_manager.cpp
 *  lae
 *
 *  Created by Kyle C Weicht on 6/7/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_resources.h"

/*----------------------------------------------------------------------------*/
/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */
#include "lae_test.h"
/*----------------------------------------------------------------------------*/

namespace
{
/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
TEST(CreateAndDestroyResourceManager)
{
    lae_resource_manager_t* manager = lae_resource_manager_create();
    CHECK_POINTER_NOT_NULL(manager);
    lae_resource_manager_destroy(manager);
}
TEST(CanLoadResource)
{
//    lae_resource_manager_t* manager = lae_resource_manager_create();
//    lae_resource_t* resource = lae_resource_manager_load(manager, "test_resource.test");
//    CHECK_POINTER_NOT_NULL(resource);
//    lae_resource_manager_destroy(manager);
}

} // anonymous namespace

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
