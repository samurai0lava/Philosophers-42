#include "philo.h"

__U64_TYPE get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
	return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

int precise_usleep(long usec)
{
	struct timeval start, current;
	long			elapsed;
	long			rem;

	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		if (gettimeofday(&current, NULL) == -1)
		{
			perror("gettimeofday");
			return (-1);
		}
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
		{
			if (usleep(rem / 2) == -1)
			{
				perror("usleep");
				return (-1);
			}
		}
	}
	return (0);
}

__U64_TYPE get_time(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
        return (0);
    return ((tv.tv_sec * (__U64_TYPE)1000) + (tv.tv_usec / 1000));
}


// int	main(void)
// {
// 	__U64_TYPE time;

// 	time = get_time();
// 	if(time == -1)
// 		return (1);
// 	else
// 		printf("tv_usec: %ld\n", time);
// 	return (0);
// }