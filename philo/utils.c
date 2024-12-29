/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:36:16 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/29 20:13:35 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].philo_data.numb_of_philos)
	{
		pthread_mutex_destroy(&philos[0].data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos[0].data.print);
	pthread_mutex_destroy(&philos[0].data.dead);
	pthread_mutex_destroy(&philos[0].data.state_mutex);
	pthread_mutex_destroy(&philos[0].data.eats);
	free(philos[0].data.forks);
	free(philos[0].data.is_dead);
	free(philos);
}

int	create_thread_monitor(t_philo *philos)
{
	if (pthread_create(&philos[0].data.monitor_thread, NULL, monitor,
			philos) != 0)
		return (1);
	return (0);
}

int	creath_thread(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos->philo_data.numb_of_philos > i)
	{
		if (pthread_create(&philos[i].philo_thread, NULL, routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
