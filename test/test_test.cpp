/*
 *  test_test.cpp
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

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
TEST(CanMakeTest)
{
}

IGNORE_TEST(CanFailATest)
{
    FAIL("Failure!");
}

TEST(CheckIntEqual)
{
    CHECK_EQUAL(33, 33);
    CHECK_NOT_EQUAL(-56, 56);
}
TEST(CheckIntLTGT)
{
    CHECK_LESS_THAN(458, 558);
    CHECK_GREATER_THAN(-564, -664);
    CHECK_LESS_THAN_EQUAL(458, 558);
    CHECK_LESS_THAN_EQUAL(458, 458);
    CHECK_GREATER_THAN_EQUAL(-564, -564);
    CHECK_GREATER_THAN_EQUAL(-564, -664);
}
TEST(CheckPointerEqual)
{
    int* a = (int*)0xDEADBEEF;
    int* b = (int*)0xDEADBEEF;
    int* c = (int*)0xBEEFDEAD;
    int* d = 0;
    CHECK_POINTER_EQUAL(a, b);
    CHECK_POINTER_NOT_EQUAL(a, c);
    CHECK_POINTER_NULL(d);
    CHECK_POINTER_NOT_NULL(a);
}

} // anonymous namespace

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
