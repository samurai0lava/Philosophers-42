/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:57:24 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/30 20:35:12 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_occured(t_philo *philo)
{
	if (pthread_mutex_lock(philo[0].data.dead) != 0)
		return (-1);
	(*philo[0].data.is_dead) = 1;
	if (pthread_mutex_unlock(philo[0].data.dead) != 0)
		return (-1);
	return (0);
}

int	check_philo_death(t_philo *philo, long long current_time)
{
	if (pthread_mutex_lock(&philo[0].data.state_mutex))
		return (-1);
	if (current_time - philo->last_meal_time > philo->philo_data.time_to_die
		&& philo[0].data.is_eating == 0)
	{
		if (pthread_mutex_unlock(&philo[0].data.state_mutex))
			return (-1);
		return (1);
	}
	if (pthread_mutex_unlock(&philo[0].data.state_mutex))
		return (-1);
	return (0);
}

static int	check_philosopher_status(t_philo *philo)
{
	long long	current_time;

	current_time = get_time();
	if (check_philo_death(philo, current_time) == 1)
	{
		printf_state(philo, PHILO_DEAD);
		if (death_occured(philo) != 0)
			return (-1);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;
	int		status;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].philo_data.numb_of_philos)
		{
			status = check_philosopher_status(&philos[i]);
			if (status != 0)
				return (NULL);
			i++;
		}
		if (check_if_all_ate(philos) != 0)
		{
			if (death_occured(philos) != 0)
				return (NULL);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_is_dead(t_philo *philos)
{
	if (pthread_mutex_lock(philos[0].data.dead) != 0)
		return (-1);
	if ((*philos[0].data.is_dead) == 1)
		return (pthread_mutex_unlock(philos[0].data.dead), 1);
	if (pthread_mutex_unlock(philos[0].data.dead) != 0)
		return (-1);
	return (0);
}
