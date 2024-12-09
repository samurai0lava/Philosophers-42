/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:36:16 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/09 19:15:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo_all *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].philo_data.numb_of_philos)
	{
		if (pthread_mutex_destroy(&philos->data.forks[i]) != 0)
			return ;
		i++;
	}
	if (pthread_mutex_destroy(&philos->data.print) != 0)
		return ;
	if (pthread_mutex_destroy(&philos->data.dead) != 0)
		return ;
	if (pthread_mutex_destroy(&philos->data.state_mutex))
		return ;
	if (pthread_mutex_destroy(&philos->data.eats))
		return ;
	free(philos->data.forks);
	free(philos->philos);
	free(philos);
}

int	create_thread_monitor(t_philo_all *philos)
{
	int	check;

	check = pthread_create(&philos->data.monitor_thread, NULL, &monitor,
			(void *)philos);
	if (check != 0)
		return (1);
	return (0);
}

int	creath_thread(t_philo_all *philos)
{
	int	i;

	i = 0;
	while (philos->philo_data.numb_of_philos > i)
	{
		if (pthread_create(&philos->philos[i].philo_thread, NULL, &routine,
				(void *)philos) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philos->philo_data.numb_of_philos)
	{
		if (pthread_join(philos->philos[i].philo_thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
