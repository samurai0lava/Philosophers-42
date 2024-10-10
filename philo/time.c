/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:00:05 by samurai0lav       #+#    #+#             */
/*   Updated: 2024/10/10 19:00:11 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

unsigned long long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL);
}
