/*
 *  main.cpp
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
/*----------------------------------------------------------------------------*/

namespace
{
/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/


} // anonymous namespace

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
int main(int argc, const char* argv[])
{
    for(int ii=1; ii<argc; ++ii)
    {
        if(strcmp("-t", argv[ii]))
            return run_all_tests(argc, argv);
    }
    return 0;
}
