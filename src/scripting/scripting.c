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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

static void _print_lua_error(lua_State* L)
{
    printf("Lua error: %s\n", luaL_checkstring(L, -1));
    lua_pop(L, 1);
}
#define ERROR_CASE(error) case error: return #error
static const char* _get_lua_error_as_string(int error)
{
    switch(error)
    {
        ERROR_CASE(LUA_OK);
        ERROR_CASE(LUA_ERRRUN);
        ERROR_CASE(LUA_ERRERR);
        ERROR_CASE(LUA_ERRMEM);
        ERROR_CASE(LUA_ERRGCMM);
        default: return "UNKNOWN";
    }
}
static void _print_lua_stack(lua_State* L)
{
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING: {  /* strings */
                printf("'%s'", lua_tostring(L, i));
                break;
            }
            case LUA_TBOOLEAN: {  /* booleans */
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;
            }
            case LUA_TNUMBER: {  /* numbers */
                printf("%g", lua_tonumber(L, i));
                break;
            }
            default: {  /* other values */
                printf("%s", lua_typename(L, t));
                break;
            }
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
lae_scripting_t* lae_scripting_create(void)
{
    lae_scripting_t* scripting = (lae_scripting_t*)malloc(sizeof(*scripting));
    assert(scripting);
    if(scripting == NULL) { return NULL; }

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
void lae_scripting_print_error(lae_scripting_t* scripting)
{
    _print_lua_error(scripting->lua);
}
int lae_scripting_run(lae_scripting_t* scripting, const char* script)
{
    int result = luaL_dostring(scripting->lua, script);
    return result;
}
int lae_scripting_validate(lae_scripting_t* scripting, const char* script)
{
    int result = luaL_loadstring(scripting->lua, script);
    lua_pop(scripting->lua, 1);
    return (result != LUA_OK);
}
int lae_scripting_call_function(lae_scripting_t* scripting,
                                const char* function,
                                const lae_script_value_t* arguments,
                                lae_script_value_t* ret)
{
    int result = 0;
    int num_arguments = 0;
    int num_returns = 0;
    
    lua_getglobal(scripting->lua, function);
    if(lua_type(scripting->lua, -1) != LUA_TFUNCTION)
    {
        /* There is no function by this name */
        lua_pop(scripting->lua, 1);
        if(ret)
        {
            ret->type = LAE_NONE;
        }
        return 1;
    }
    
    while(arguments && arguments->type != LAE_NONE)
    {
        switch(arguments->type)
        {
        case LAE_STRING:
            lua_pushstring(scripting->lua, arguments->value.string);
            break;
        case LAE_INT:
            lua_pushinteger(scripting->lua, arguments->value.i);
            break;
        case LAE_FLOAT:
            lua_pushnumber(scripting->lua, arguments->value.f);
            break;
        case LAE_PTR:
            lua_pushlightuserdata(scripting->lua, arguments->value.ptr);
            break;
        default:
            assert(0);
            break;
        }
        
        ++arguments;
        ++num_arguments;
    }
    
    if(ret)
    {
        num_returns = 1;
    }
    
    result = lua_pcall(scripting->lua, num_arguments, num_returns, 0);
    if(result != 0)
    {
        printf("Error running function %s: ", function);
        printf("%s\n", _get_lua_error_as_string(result));
        _print_lua_error(scripting->lua);
        _print_lua_stack(scripting->lua);
        return 1;
    }
    
    if(ret)
    {
        switch(lua_type(scripting->lua, -1))
        {
        case LUA_TSTRING:
            ret->type = LAE_STRING;
            ret->value.string = luaL_checkstring(scripting->lua, -1);
            break;
        case LUA_TNUMBER:
            ret->value.f = (float)luaL_checknumber(scripting->lua, -1);
            ret->type = LAE_FLOAT;
            if(floorf(ret->value.f) == ret->value.f)
            {
                ret->type = LAE_INT;
                ret->value.i = (int)ret->value.f;
            }
            break;
        case LUA_TUSERDATA:
            ret->type = LAE_PTR;
            ret->value.ptr = lua_touserdata(scripting->lua, -1);
            break;
        default:
            ret->type = LAE_NONE;
            break;
        }
    }
    
    return 0;
}

int lae_scripting_export_function(  lae_scripting_t* scripting, 
                                    const char* function_name,
                                    int (*function)(struct lua_State*))
{
    lua_register(scripting->lua, function_name, function);
    return 0;
}
int lae_scripting_export_functions(lae_scripting_t* scripting, const lae_scripting_function_t* functions)
{
    while(functions && functions->name && functions->func)
    {
        lae_scripting_export_function(scripting, functions->name, functions->func);
        functions++;
    }
    return 0;
}
lae_script_value_t lae_scripting_get_value(lae_scripting_t* scripting, const char* name)
{
    lae_script_value_t ret;
    lua_getglobal(scripting->lua, name);
    switch(lua_type(scripting->lua, -1))
    {
    case LUA_TSTRING:
        ret.type = LAE_STRING;
        ret.value.string = luaL_checkstring(scripting->lua, -1);
        break;
    case LUA_TNUMBER:
        ret.value.f = (float)luaL_checknumber(scripting->lua, -1);
        ret.type = LAE_FLOAT;
        if(floorf(ret.value.f) == ret.value.f)
        {
            ret.type = LAE_INT;
            ret.value.i = (int)ret.value.f;
        }
        break;
    case LUA_TUSERDATA:
        ret.type = LAE_PTR;
        ret.value.ptr = lua_touserdata(scripting->lua, -1);
        break;
    default:
        ret.type = LAE_NONE;
        break;
    }
    return ret;
}
void lae_scripting_set_value(lae_scripting_t* scripting, const char* name, lae_script_value_t val)
{
    switch(val.type)
    {
    case LAE_STRING:
        lua_pushstring(scripting->lua, val.value.string);
        break;
    case LAE_INT:
        lua_pushinteger(scripting->lua, val.value.i);
        break;
    case LAE_FLOAT:
        lua_pushnumber(scripting->lua, val.value.f);
        break;
    case LAE_PTR:
        lua_pushlightuserdata(scripting->lua, val.value.ptr);
        break;
    default:
        assert(0);
        break;
    }
    lua_setglobal(scripting->lua, name);
}

float lae_scripting_float_from_lua(struct lua_State* L, int index)
{
    return (float)luaL_checknumber(L, index);
}
const char* lae_scripting_string_from_lua(struct lua_State* L, int index)
{
    return luaL_checkstring(L, index);
}
intptr_t lae_scripting_int_from_lua(struct lua_State* L, int index)
{
    return luaL_checkinteger(L, index);
}
void* lae_scripting_ptr_from_lua(struct lua_State* L, int index)
{
    return lua_touserdata(L, index);
}

void lae_scripting_float_to_lua(struct lua_State* L, float value)
{
    lua_pushnumber(L, value);
}
void lae_scripting_string_to_lua(struct lua_State* L, const char* value)
{
    lua_pushstring(L, value);
}
void lae_scripting_int_to_lua(struct lua_State* L, intptr_t value)
{
    lua_pushinteger(L, value);
}
void lae_scripting_ptr_to_lua(struct lua_State* L, void* value)
{
    lua_pushlightuserdata(L, value);
}
