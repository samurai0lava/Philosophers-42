
#include "philo.h"



int precise_usleep(long usec)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < usec)
		usleep(500);
	return (0);
}

// Gets the current time in milliseconds

long long get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return -1;
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}