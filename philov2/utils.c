/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:36:16 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/19 12:00:08 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo *philos)
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
	philos->data.forks = NULL;
	free(philos);
	philos = NULL;
}

int create_thread_monitor(t_philo *philos)
{
    if (pthread_create(&philos->data.monitor_thread, NULL, &monitor, philos) != 0)
        return (1);
    return (0);
}

int	creath_thread(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos->philo_data.numb_of_philos > i)
	{
		if (pthread_create(&philos[i].philo_thread, NULL, &routine,
			&philos[i]) != 0)
			return (1);
		i++;
	}
    i = 0;
    while(philos->philo_data.numb_of_philos > i)
    {
        if(pthread_join(philos[i].philo_thread, NULL) != 0)
            return (1);
        i++;
    }
	return (0);
}
