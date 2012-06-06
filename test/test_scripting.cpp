/*
 *  test_scripting.cpp
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
#include "lae_scripting.h"
/*----------------------------------------------------------------------------*/

/*
 *  Tests:
 *      *Initialize scripting interface
 *          *Lua
 *          V8 Javascript
 *      *Shutdown scripting interface
 *      *Run "Hello World" script
 *      *Call script function
 *      *Export C function
 *      *Call C function
 *      Export C function with custom type
 */
 
namespace
{
lae_scripting_t* g_scripting = NULL;

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
TEST(InitializeShutdownScripting)
{
    lae_scripting_t* scripting = lae_scripting_create();
    CHECK_POINTER_NOT_NULL(scripting);
    lae_scripting_destroy(scripting);
    
    // Create a script interface for the rest of the tests
    g_scripting = lae_scripting_create();
    CHECK_POINTER_NOT_NULL(g_scripting);
}
TEST(HelloWorld)
{
    const char lua_hello_world[] = "local x = 1";
    int result = lae_scripting_run(g_scripting, lua_hello_world);
    CHECK_FALSE(result);
}
TEST(ScriptFails)
{
    const char fail_script[] = "print(\"Hello world!\"";
    int result = lae_scripting_run(g_scripting, fail_script);
    CHECK_TRUE(result);
}
TEST(CallLuaFunction)
{
    const char script[] = 
    "function test_func1()  \n"
    "   local x = 1         \n"
    "end                    \n";
    int result = lae_scripting_run(g_scripting, script);
    CHECK_FALSE(result);
    
    result = lae_scripting_call_function(g_scripting, "test_func1", NULL, NULL);
    CHECK_FALSE(result);
}
TEST(CallRealLuaFunction)
{
    const char script[] = 
    "function test_func2(x, y)  \n"
    "   return x + y            \n"
    "end                        \n";
    int result = lae_scripting_run(g_scripting, script);
    CHECK_FALSE(result);
    
    lae_script_value_t ret;
    lae_script_value_t parameters[] =
    {
        { LAE_FLOAT, 0 },
        { LAE_FLOAT, 0 },
        { LAE_NONE,  0 },
    };
    parameters[0].value.f = 1.3f;
    parameters[1].value.f = -4.5f;
    
    result = lae_scripting_call_function(g_scripting, "test_func2", parameters, &ret);
    CHECK_FALSE(result);
    CHECK_EQUAL(LAE_FLOAT, ret.type);
    CHECK_EQUAL_FLOAT(parameters[0].value.f+parameters[1].value.f, ret.value.f);
}
static float test_func_c(float a, float b)
{
    return a + b;
}
static int test_func_c_lua(struct lua_State* L)
{
    float a = lae_scripting_float_from_lua(L, 1);
    float b = lae_scripting_float_from_lua(L, 2);
    float result = test_func_c(a, b);
    lae_scripting_float_to_lua(L, result);
    return 1;
}

typedef struct
{
    int     i;
    float   f;
} custom_type_t;

static void change_custom_type(custom_type_t* t, int i, float f)
{
    t->i = i;
    t->f = f;
}
static int change_custom_type_lua(struct lua_State* L)
{
    custom_type_t* t = (custom_type_t*)lae_scripting_ptr_from_lua(L, 1);
    int i = (int)lae_scripting_int_from_lua(L, 2);
    float f = lae_scripting_float_from_lua(L, 3);
    change_custom_type(t, i, f);
    return 0;
}

TEST(ExportCFunction)
{
    int result = lae_scripting_export_function(g_scripting, "test_func_c", test_func_c_lua);
    CHECK_FALSE(result);
}
TEST(LuaCallCFunction)
{
    const char script[] =
    "function test_func3()              \n"
    "   return test_func_c(-1.3, 4.5)   \n"
    "end                                \n";
    int result = lae_scripting_run(g_scripting, script);
    CHECK_FALSE(result);
    
    lae_script_value_t ret;
    result = lae_scripting_call_function(g_scripting, "test_func3", NULL, &ret);
    CHECK_FALSE(result);
    CHECK_EQUAL(LAE_FLOAT, ret.type);
    CHECK_EQUAL_FLOAT(-1.3f+4.5f, ret.value.f);
}
TEST(UseCustomType)
{
    lae_scripting_export_function(g_scripting, "change_custom_type", change_custom_type_lua);
    custom_type_t type = { -345, 987.65f };
    CHECK_EQUAL(-345, type.i);
    CHECK_EQUAL_FLOAT(987.65f, type.f);
    
    lae_script_value_t params[] = 
    {
        { LAE_PTR, 0 },
        { LAE_INT, 0 },
        { LAE_FLOAT, 0 },
        { LAE_NONE, 0 },
    };
    params[0].value.ptr = (void*)&type;
    params[1].value.i = 123;
    params[2].value.f = 654.32f;
    int result = lae_scripting_call_function(g_scripting, "change_custom_type", params, NULL);
    CHECK_FALSE(result);
    CHECK_EQUAL(123, type.i);
    CHECK_EQUAL_FLOAT(654.32f, type.f);
}
TEST(GetValueFromLua)
{
    const char script[] = 
    "test_int    = 42           \n"
    "test_float  = -805.84      \n"
    "test_string = \"String?\"  \n"
    "test_null   = nil          \n";
    lae_scripting_run(g_scripting, script);
    
    lae_script_value_t val;
    val = lae_scripting_get_value(g_scripting, "test_int");
    CHECK_EQUAL(LAE_INT, val.type);
    CHECK_EQUAL(42, val.value.i);
    val = lae_scripting_get_value(g_scripting, "test_float");
    CHECK_EQUAL(LAE_FLOAT, val.type);
    CHECK_EQUAL_FLOAT(-805.84f, val.value.f);
    val = lae_scripting_get_value(g_scripting, "test_string");
    CHECK_EQUAL(LAE_STRING, val.type);
    CHECK_EQUAL_STRING("String?", val.value.string);    
    val = lae_scripting_get_value(g_scripting, "test_null");
    CHECK_EQUAL(LAE_NONE, val.type);
    
    val = lae_scripting_get_value(g_scripting, "not_a_value");
    CHECK_EQUAL(LAE_NONE, val.type);
}
TEST(SetLuaValue)
{
    const char script[] = 
    "test_int    = 42           \n"
    "test_float  = -805.84      \n"
    "test_string = \"String?\"  \n"
    "test_null   = nil          \n";
    lae_scripting_run(g_scripting, script);
    
    lae_script_value_t val;
    val = lae_scripting_get_value(g_scripting, "test_int");
    CHECK_EQUAL(LAE_INT, val.type);
    CHECK_EQUAL(42, val.value.i);
    val.type = LAE_INT;
    val.value.i = -97;
    lae_scripting_set_value(g_scripting, "test_int", val);
    val = lae_scripting_get_value(g_scripting, "test_int");
    CHECK_EQUAL(LAE_INT, val.type);
    CHECK_EQUAL(-97, val.value.i);
    val.type = LAE_STRING;
    val.value.string = "lol";
    lae_scripting_set_value(g_scripting, "test_int", val);
    val = lae_scripting_get_value(g_scripting, "test_int");
    CHECK_EQUAL(LAE_STRING, val.type);
    CHECK_EQUAL_STRING("lol", val.value.string);
}
TEST(ValidateScript)
{
    const char script[] =
    "function test_func4(a, b, c)   \n"
    "   return (a*b)+c;             \n"
    "end                            \n";
    char script_buffer[256];
    strcpy(script_buffer, script);
    
    int result = lae_scripting_validate(g_scripting, script_buffer);
    CHECK_EQUAL(0, result);
    script_buffer[7] = 'a';
    result = lae_scripting_validate(g_scripting, script_buffer);
    CHECK_EQUAL(1, result);
}

} // anonymous namespace

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
