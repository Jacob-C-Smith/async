/** !
 * Example async program
 * 
 * @file main.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>

// log
#include <log/log.h>

// async
#include <async/async.h>

// Enumeration definitions
enum async_examples_e
{
    ASYNC_1_EXAMPLE         = 0,
    ASYNC_2_EXAMPLE         = 1,
    ASYNC_3_EXAMPLE         = 2,
    ASYNC_4_EXAMPLE         = 3,
    ASYNC_EXAMPLES_QUANTITY = 4
};

enum async_example_results_e
{
    RESULT_SUCCSS,  // = 0
    RESULT_FAILURE, // = 1
    RESULT_TIMEOUT, // = 2
    RESULT_QUANTITY // = 3... len([0, 1, 2]) = 3
};

// Forward declarations
/** !
 * Print a usage message to standard out
 * 
 * @param argv0 the name of the program
 * 
 * @return void
 */
void print_usage ( const char *argv0 );

/** !
 * Parse command line arguments
 * 
 * @param argc            the argc parameter of the entry point
 * @param argv            the argv parameter of the entry point
 * @param examples_to_run return
 * 
 * @return void on success, program abort on failure
 */
void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run );

/** !
 * Thread example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int async_1_example ( int argc, const char *argv[] );

int async_task ( promise *p_promise )
{
    return 1;
}

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Initialized data
    bool examples_to_run[ASYNC_EXAMPLES_QUANTITY] = { 0 };

    // Parse command line arguments
    parse_command_line_arguments(argc, argv, examples_to_run);

    // Initialize parallel
    if ( async_init() == 0 ) goto failed_to_initialize_parallel;

    // Formatting
    printf(
        "╭───────────────╮\n"\
        "│ async example │\n"\
        "╰───────────────╯\n"\
        "The async library provides high level abstractions for asynchronous computing.\n"\
        "Async provides %d abstractions. TODO: what abstractions\n\n"\
        "TODO: Document abstraction A.\n"\
        "TODO: Document abstraction B.\n"\
        "TODO: Document abstraction C.\n",
        ASYNC_EXAMPLES_QUANTITY
    );

    //////////////////////
    // Run the examples //
    //////////////////////

    // Run the thread example program
    if ( examples_to_run[ASYNC_1_EXAMPLE] )

        // Error check
        if ( async_1_example(argc, argv) == 0 ) goto failed_to_run_thread_example;

    // Clean up async
    async_quit();

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {
        
        failed_to_initialize_parallel:

            // Write an error message to standard out
            printf("Failed to initialize parallel!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_thread_example:

            // Print an error message
            printf("Failed to run thread example!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_thread_pool_example:

            // Print an error message
            printf("Failed to run thread pool example!\n");

            // Error
            return EXIT_FAILURE;
        
        failed_to_run_schedule_example:
            
            // Print an error message
            printf("Failed to run schedule example!\n");

            // Error
            return EXIT_FAILURE;   
    }
}

void print_usage ( const char *argv0 )
{

    // Argument check
    if ( argv0 == (void *) 0 ) exit(EXIT_FAILURE);

    // Print a usage message to standard out
    printf("Usage: %s [thread] [thread-pool] [schedule]\n", argv0);

    // Done
    return;
}

void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run )
{

    // If no command line arguments are supplied, run all the examples
    if ( argc == 1 ) goto all_examples;

    // Error check
    if ( argc > ASYNC_EXAMPLES_QUANTITY + 1 ) goto invalid_arguments;

    // Iterate through each command line argument
    for (size_t i = 1; i < argc; i++)
    {
        
        // Thread example?
        if ( strcmp(argv[i], "async1") == 0 )

            // Set the thread example flag
            examples_to_run[ASYNC_1_EXAMPLE] = true;

        // Thread pool example?
        else if ( strcmp(argv[i], "async2") == 0 )
            
            // Set the thread pool example flag
            examples_to_run[ASYNC_2_EXAMPLE] = true;

        // Schedule example?
        else if ( strcmp(argv[i], "async3") == 0 )

            // Set the schedule example flag
            examples_to_run[ASYNC_3_EXAMPLE] = true;
        
        // Default
        else goto invalid_arguments;
    }
    
    // Success
    return;

    // Set each example flag
    all_examples:
    {

        // For each example ...
        for (size_t i = 0; i < ASYNC_EXAMPLES_QUANTITY; i++)
        
            // ... set the example flag
            examples_to_run[i] = true;
        
        // Success
        return;
    }

    // Error handling
    {

        // Argument errors
        {
            invalid_arguments:
                
                // Print a usage message to standard out
                print_usage(argv[0]);

                // Abort
                exit(EXIT_FAILURE);
        }
    }
}

int then1 ( promise *p_promise )
{
    p_promise->i++;
    
    printf("%d : from %s\n", p_promise->i, __FUNCTION__); fflush(stdout);
    
    return RESULT_SUCCSS;
}

int then2 ( promise *p_promise )
{
    p_promise->i += 2;
    
    printf("%d : from %s\n", p_promise->i, __FUNCTION__); fflush(stdout);
    
    return RESULT_SUCCSS;
}

int async_1_example ( int argc, const char *argv[] )
{
    
    // Supress warnings
    (void) argc;
    (void) argv;

    // Formatting
    printf(
        "╭─────────────────╮\n"\
        "│ async 1 example │\n"\
        "╰─────────────────╯\n"\
        "TODO: Description.\n\n"
    );

    // Initialized data
    fn_async_task *pfn_async_task = async_task;
    promise        _promise       = { 0 };
    
    // Evaluate an async function
    _promise = async(&_promise, pfn_async_task, &_promise)
        .then(&_promise, then1)
        .then(&_promise, then2);
    
    // TODO
    //await(p_promise);

    // Success
    return 1;

    // Error handling
    {

        // Parallel errors
        {
            failed_to_start_thread:

                // Write an error message to standard out
                log_error("Failed to create parallel thread in call to function \"%s\"\n", __FUNCTION__);

                // Error
                return 0;

            failed_to_join_thread:
                
                // Write an error message to standard out
                log_error("Failed to join parallel thread in call to function \"%s\"\n", __FUNCTION__);

                // Error
                return 0;
        }
    }
}
