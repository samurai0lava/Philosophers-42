/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:25:33 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/28 19:43:20 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	precise_usleep(long usec)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < usec)
		usleep(500);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	return_error(char *str)
{
	printf(MAGENTA "%s" RESET, str);
	return (-1);
}

int	allocate_what_i_need(t_philo *philo)
{
	philo[0].data.forks = malloc(sizeof(pthread_mutex_t)
			* philo->philo_data.numb_of_philos);
	if (!philo[0].data.forks)
		return (1);
	philo[0].data.is_dead = malloc(sizeof(int));
	if (!philo[0].data.is_dead)
		return (free(philo[0].data.forks), 1);
	philo[0].data.dead = malloc(sizeof(pthread_mutex_t));
	if (!philo[0].data.dead)
		return (free(philo[0].data.is_dead), free(philo[0].data.forks), 1);
	philo[0].data.eats = malloc(sizeof(pthread_mutex_t));
	if (!philo[0].data.eats)
		return (free(philo[0].data.is_dead), free(philo[0].data.forks),
			free(philo[0].data.dead), 1);
	philo[0].data.print = malloc(sizeof(pthread_mutex_t));
	if (!philo[0].data.print)
	{
		return (free(philo[0].data.is_dead), free(philo[0].data.forks),
			free(philo[0].data.dead), free(philo[0].data.print), 1);
	}
	return (0);
}
