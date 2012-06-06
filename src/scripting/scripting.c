/*
 *  scripting.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_scripting.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdlib.h>
/* External headers */
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
/* Internal headers */
#include "lae_assert.h"
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
struct lae_scripting_t
{
    lua_State*  lua;
};

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
lae_scripting_t* lae_scripting_create(void)
{
    lae_scripting_t* scripting = (lae_scripting_t*)malloc(sizeof(*scripting));
    assert(scripting);

    { /* Initialize Lua */
        scripting->lua = luaL_newstate();
        assert(scripting->lua);
        luaL_openlibs(scripting->lua);
    }

    return scripting;
}
void lae_scripting_destroy(lae_scripting_t* script)
{
    { /* Shutdown Lua */
        lua_close(script->lua);
    }

    free(script);
}
