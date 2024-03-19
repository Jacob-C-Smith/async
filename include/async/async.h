/** !
 * High level abstractions for asynchronous programming
 * 
 * @file async/async.h
 *
 * @author Jacob Smith
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// sync
#include <sync/sync.h>

// log
#include <log/log.h>

// dict
#include <dict/dict.h>

// parallel
#include <parallel/parallel.h>
#include <parallel/thread.h>

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Set the reallocator for the dict submodule
#ifdef DICT_REALLOC
    #undef DICT_REALLOC
    #define DICT_REALLOC(p, sz) realloc(p, sz)
#endif

// Set the reallocator for the array submodule
#ifdef ARRAY_REALLOC
    #undef ARRAY_REALLOC
    #define ARRAY_REALLOC(p, sz) realloc(p, sz)
#endif

// Set the reallocator for the json submodule
#ifdef JSON_REALLOC
    #undef JSON_REALLOC
    #define JSON_REALLOC(p, sz) realloc(p, sz)
#endif

// Set the reallocator for the parallel submodule
#ifdef PARALLEL_REALLOC
    #undef PARALLEL_REALLOC
    #define PARALLEL_REALLOC(p, sz) realloc(p, sz)
#endif

// Memory management macro
#ifndef ASYNC_REALLOC
    #define ASYNCL_REALLOC(p, sz) realloc(p,sz)
    #define ASYNC_FREE(p) free(p)
#endif

// Forward declarations
struct promise_s;
typedef void *(*fn_async_task)(void *);

// Type definitions
typedef struct promise_s promise;

// Structure definitions
struct promise_s
{
    int i;
    promise (*then)(promise *p_promise, int (*pfn_then) ( promise *p_promise ));
};

DLLEXPORT promise then ( promise *p_promise, int (*pfn_then) ( promise *p_promise ) );

// Initializers
/** !
 * Initialize async 
 * 
 * @param void
 * 
 * @return 1 on success, 0 on error 
 */ 
DLLEXPORT int async_init ( void );

/** !
 * 
 */
DLLEXPORT promise async ( promise *p_promise, fn_async_task *pfn_async_task, void *p_parameter );

/** !
 * 
 */
DLLEXPORT int await ( promise *p_promise );

/** !
 * Clean up async 
 * 
 * @param void
 * 
 * @return 1 on success, 0 on error 
 */ 
DLLEXPORT void async_quit ( void );
