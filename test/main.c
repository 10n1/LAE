/*
 *  main.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */

/*----------------------------------------------------------------------------*/
/* C headers */
/* External headers */
/* Internal headers */
#include "lae_test.h"
#include "lae_assert.h"
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
int main(int argc, const char* argv[])
{
    /* Pass "-t" to the app to run the tests */
    int ii;
    for(ii=1; ii<argc; ++ii)
    {
        if(strcmp(argv[ii], "-t") == 0)
            return run_all_tests(argc, argv);
    }

    return 0;
}
