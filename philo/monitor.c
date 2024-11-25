/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:57:24 by iouhssei          #+#    #+#             */
/*   Updated: 2024/11/25 13:03:03 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philos[0].shared_data.dead);
		if (philos[0].shared_data.is_dead == 1)
		{
			pthread_mutex_unlock(philos[0].shared_data.dead);
			return (NULL);
		}
		pthread_mutex_unlock(philos[0].shared_data.dead);
		if (check_if_all_ate(philos) == 1 || check_is_dead(philos) == 1)
			return (NULL);
	}
	return (arg);
}

int	check_is_dead(t_philo *philos)
{
	int			i;
	long long	current_time;

	i = 0;
	while (i < philos[0].philo_data.numb_of_philos)
	{
		current_time = get_time();
		pthread_mutex_lock(&philos[i].shared_data.state_mutex);
		pthread_mutex_lock(philos[i].shared_data.dead);
		if (current_time - philos[i].last_meal_time
			> philos[i].philo_data.time_to_die
			&& philos[i].shared_data.is_eating == 0)
		{
			printf_state(&philos[i], PHILO_DEAD);
			philos[0].shared_data.is_dead = 1;
			pthread_mutex_unlock(philos[i].shared_data.dead);
			pthread_mutex_unlock(&philos[i].shared_data.state_mutex);
			return (1);
		}
		pthread_mutex_unlock(philos[i].shared_data.dead);
		pthread_mutex_unlock(&philos[i].shared_data.state_mutex);
		i++;
	}
	return (0);
}

int dead_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_data.dead);
	if (philo->shared_data.is_dead == 1)
	{
		pthread_mutex_unlock(philo->shared_data.dead);
		return (1);
	}
	pthread_mutex_unlock(philo->shared_data.dead);
	return (0);
}

int pthread_mutex_philo(t_philo *philos)
{
	int	i;

	if (pthread_mutex_init(philos[0].shared_data.print, NULL)
		|| pthread_mutex_init(philos[0].shared_data.dead, NULL)
		|| pthread_mutex_init(&philos[0].shared_data.state_mutex, NULL)
		|| pthread_mutex_init(&philos[0].shared_data.eats, NULL))
		return (1);
	i = 0;
	while (i < philos[0].philo_data.numb_of_philos)
	{
		if (pthread_mutex_init(&philos[0].shared_data.forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
