/*
 *  test.cpp
 *  lae
 *
 *  Created by Kyle C Weicht on 6/5/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
#include "lae_test.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <stdio.h>
/* C++ headers */
/* External headers */
/* Internal headers */
#include "lae_defines.h"
/*----------------------------------------------------------------------------*/

#if defined(__APPLE__) || defined(__GNUG__)
    #define ERROR_FORMAT "%s:%d: error: "
#else
    #define ERROR_FORMAT "%s(%d): error: "
#endif

namespace
{
/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
enum { MAX_TESTS = 1024*4 };

enum TestResult
{
    ePass,
    eFail,
    eIgnore
};

test_func_t*    _tests[MAX_TESTS];
int             _num_tests = 0;
int             _num_tests_passed = 0;
int             _num_tests_failed = 0;
int             _num_tests_ignored = 0;
TestResult      _current_test_result = ePass;

void _ignore_test(void)
{
    _current_test_result = eIgnore;
}

} // anonymous namespace

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
int register_test(test_func_t* test)
{
    int test_id = _num_tests++;
    _tests[test_id] = test;
    return test_id;
}
int ignore_test(test_func_t* test)
{
    UNUSED_PARAMETER(test);
    return register_test(&_ignore_test);
}

void fail(const char* file, int line, const char* message)
{
    printf("\n"ERROR_FORMAT"%s\n", file, line, message);
    _current_test_result = eFail;
}
void check_equal(const char* file, int line, int64_t expected, int64_t actual)
{
    if(expected != actual)
    {
        char buffer[256];
        sprintf(buffer, "Expected: %lld  Actual: %lld", expected, actual);
        fail(file,line,buffer);
    }
}
void check_not_equal(const char* file, int line, int64_t expected, int64_t actual)
{
    if(expected == actual)
    {
        char buffer[256];
        sprintf(buffer, "Actual value equals expected: %lld", actual);
        fail(file,line,buffer);
    }
}
void check_less_than(const char* file, int line, int64_t left, int64_t right)
{
    if(left >= right)
    {
        char buffer[256];
        sprintf(buffer, "%lld is not less than %lld", left, right);
        fail(file,line,buffer);
    }
}
void check_greater_than(const char* file, int line, int64_t left, int64_t right)
{
    if(left <= right)
    {
        char buffer[256];
        sprintf(buffer, "%lld is not greater than %lld", left, right);
        fail(file,line,buffer);
    }
}
void check_less_than_equal(const char* file, int line, int64_t left, int64_t right)
{
    if(left > right)
    {
        char buffer[256];
        sprintf(buffer, "%lld is not less than %lld", left, right);
        fail(file,line,buffer);
    }
}
void check_greater_than_equal(const char* file, int line, int64_t left, int64_t right)
{
    if(left < right)
    {
        char buffer[256];
        sprintf(buffer, "%lld is not greater than %lld", left, right);
        fail(file,line,buffer);
    }
}
void check_pointer_equal(const char* file, int line, const void* expected, const void* actual)
{
    if(expected != actual)
    {
        char buffer[256];
        sprintf(buffer, "Expected: %p  Actual: %p", expected, actual);
        fail(file,line,buffer);
    }
}
void check_pointer_not_equal(const char* file, int line, const void* expected, const void* actual)
{
    if(expected == actual)
    {
        char buffer[256];
        sprintf(buffer, "Actual value equals expected: %p", actual);
        fail(file,line,buffer);
    }
}
void check_pointer_null(const char* file, int line, const void* pointer)
{
    if(pointer != NULL)
    {
        char buffer[256];
        sprintf(buffer, "Pointer is not NULL: %p", pointer);
        fail(file,line,buffer);
    }
}
void check_pointer_not_null(const char* file, int line, const void* pointer)
{
    if(pointer == NULL)
    {
        char buffer[256];
        sprintf(buffer, "Pointer is NULL");
        fail(file,line,buffer);
    }
}
void check_true(const char* file, int line, bool value)
{
    if(!value)
    {
        char buffer[] = "False";
        fail(file, line, buffer);
    }
}
void check_false(const char* file, int line, bool value)
{
    if(value)
    {
        char buffer[] = "False";
        fail(file, line, buffer);
    }
}
int run_all_tests(int, const char*[])
{
    for(int ii=0; ii<_num_tests; ++ii)
    {
        _current_test_result = ePass;
        _tests[ii]();
        switch(_current_test_result)
        {
        case ePass: _num_tests_passed++; printf("."); break;
        case eFail: _num_tests_failed++; break;
        case eIgnore: _num_tests_ignored++; printf("!"); break;
        }
    }
    printf("\n--------------------------------------\n");
    printf("%d failed, %d passed, %d ignored, %d total\n", 
            _num_tests_failed, _num_tests_passed, _num_tests_ignored, _num_tests);
    return _num_tests_failed;
}
