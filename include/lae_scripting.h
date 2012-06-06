/*
 *  lae_scripting.h
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#ifndef __lae_lae_scripting_h_
#define __lae_lae_scripting_h_

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdint.h>
#include <stddef.h>
/* C++ headers */
/* External headers */
/* Internal headers */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" { // Use C linkage
#endif

/**
 * The struct that holds all the necessary scripting handles
 */
struct lua_State;
typedef struct lae_scripting_t lae_scripting_t;

typedef enum
{
    LAE_NONE = 0,
    LAE_FLOAT,
    LAE_INT,
    LAE_STRING,
    LAE_PTR
} lae_script_value_type_e;

typedef struct
{
    lae_script_value_type_e type;
    union
    {
        const char* string;
        void*       ptr;
        ptrdiff_t   i;
        float       f;
    } value;
} lae_script_value_t;

/**
 * Allocates and initalizes a scripting interface
 */
lae_scripting_t* lae_scripting_create(void);

/**
 * Tears down the scripting interface and clears the memory
 */
void lae_scripting_destroy(lae_scripting_t* script);

/**
 * Prints the last error message 
 */
void lae_scripting_print_error(lae_scripting_t* scripting);

/**
 * Compiles and runs a script
 */
int lae_scripting_run(lae_scripting_t* scripting, const char* script);

/**
 * Validates (compiles) a script.
 * Doesn't try to run the compiled script
 */
int lae_scripting_validate(lae_scripting_t* scripting, const char* script);

/**
 * Calls a script-side function from C
 */
int lae_scripting_call_function(lae_scripting_t* scripting,
                                const char* function,
                                const lae_script_value_t* arguments,
                                lae_script_value_t* ret);
/**
 * Exports a C function for use from the script interface
 */
int lae_scripting_export_function(  lae_scripting_t* scripting, 
                                    const char* function_name,
                                    int (*function)(struct lua_State*));
/**
 * Retrieves or sets a global value from the scripting environment
 */
lae_script_value_t lae_scripting_get_value(lae_scripting_t* scripting, const char* name);
void lae_scripting_set_value(lae_scripting_t* scripting, const char* name, lae_script_value_t val);

/**
 * Various helper functions to get values to and from Lua
 */
float lae_scripting_float_from_lua(struct lua_State* L, int index);
const char* lae_scripting_string_from_lua(struct lua_State* L, int index);
intptr_t lae_scripting_int_from_lua(struct lua_State* L, int index);
void* lae_scripting_ptr_from_lua(struct lua_State* L, int index);

void lae_scripting_float_to_lua(struct lua_State* L, float value);
void lae_scripting_string_to_lua(struct lua_State* L, const char* value);
void lae_scripting_int_to_lua(struct lua_State* L, intptr_t value);
void lae_scripting_ptr_to_lua(struct lua_State* L, void* value);
 
#ifdef __cplusplus
}
#endif

#endif /* include guard */
