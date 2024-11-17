
#include "philo.h"

long long get_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int precise_usleep(long usec)
{
    long start;
    long elapsed;
    
    start = get_time() * 1000;
    while (1)
    {
        elapsed = (get_time() * 1000) - start;
        if (elapsed >= usec)
            break;
        usleep(100);
    }
    return (0);
}