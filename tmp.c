#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sync/sync.h>


monitor _monitor;
mutex _mutex;

int d = 1;
int c = 0;
void *foo ( void *a )
{

    mutex_lock(_mutex);

        printf("WAIT\n"); fflush(stdout);

        monitor_wait(&_monitor);

        printf("NOTIFIED\n"); fflush(stdout);
    
    mutex_unlock(_mutex);

} 

void *bar ( void *b )
{
    mutex_lock(_mutex);
        printf("NOTIFY\n"); fflush(stdout);

        monitor_notify_all(&_monitor);
    mutex_unlock(_mutex);
}

int main ( int argc, const char *argv[] )
{
    mutex_create(&_mutex);
    monitor_create(&_monitor);
    
    parallel_thread *p1, *p2;

    parallel_thread_start(&p1, foo, 0);
    parallel_thread_start(&p1, foo, 0);
    parallel_thread_start(&p1, foo, 0);
    parallel_thread_start(&p1, foo, 0);
    parallel_thread_start(&p1, foo, 0);

    sleep(1);

    parallel_thread_start(&p2, bar, 0);

    parallel_thread_join(&p2);
    parallel_thread_join(&p1);

    return 1;
}