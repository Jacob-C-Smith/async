/** !
 * High level abstractions for asynchronous programming
 * 
 * @file async.c
 *
 * @author Jacob Smith
 */

// parallel
#include <async/async.h>

// Static data
static dict *parallel_parallel_tasks = 0;

promise then ( promise *p_promise, int (*pfn_then) ( promise *p_promise ) ) 
{
    pfn_then(p_promise);

    return *p_promise;
}

promise async ( promise *p_promise, fn_async_task *pfn_async_task, void *p_parameter )
{
    
    parallel_thread *p_parallel_thread = (void *) 0;

    parallel_thread_start(&p_parallel_thread, pfn_async_task, p_parameter);
    
    p_promise->then = then;
    p_promise->i = 0;
    
    printf("%d : from %s\n", p_promise->i, __FUNCTION__); fflush(stdout);

    return (promise)
    {
        .i = p_promise->i,
        .then = p_promise->then
    };
}

int await ( promise *p_promise );

int async_init ( void ) 
{

    // Initialize log
    if ( log_init(0, true) == 0 ) goto failed_to_init_log;

    // Construct a dictionary for parallel tasks
    dict_construct(&parallel_parallel_tasks, 256, 0);

    // Success
    return 1;

    // Error handling
    {

        // log errors
        {
            failed_to_init_log:
                #ifndef NDEBUG
                    printf("[async] Failed to initialize log\n");
                #endif

                // Error
                return 0;
        }
    }
}

void async_quit ( void )
{

    // Clean up
    dict_destroy(&parallel_parallel_tasks);
}