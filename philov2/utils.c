/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:36:16 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/06 12:00:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void wait_and_cleanup(t_philo *philos, pthread_t *threads)
{
    int i;

    if (philos == NULL || threads == NULL)
        return;
    i = 0;
    while (i < philos[0].philo_data.numb_of_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_join(philos[0].shared_data.monitor_thread, NULL);
    cleanup(philos);
}

void cleanup(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos[0].philo_data.numb_of_philos)
    {
        pthread_mutex_destroy(&philos[0].shared_data.forks[i]);
        i++;
    }
    pthread_mutex_destroy(philos[0].shared_data.print);
    pthread_mutex_destroy(philos[0].shared_data.dead);
    pthread_mutex_destroy(&philos[0].shared_data.state_mutex);
    pthread_mutex_destroy(&philos[0].shared_data.eats);

    free(philos[0].shared_data.forks);
    free(philos[0].shared_data.print);
    free(philos[0].shared_data.dead);
    free(philos[0].shared_data.philos);
    free(philos);
}

int	create_thread_monitor(t_philo *philos)
{
	int	check;

	check = pthread_create(&philos[0].shared_data.monitor_thread, NULL,
			&monitor, philos);
	if (check != 0)
		return (1);
	return (0);
}

int	creath_thread(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[0].philo_data.numb_of_philos > i)
	{
		if (pthread_create(&philos[i].shared_data.philos[i], NULL, &routine,
				&philos[i]) != 0)
			return (1);
		if (pthread_detach(philos[i].shared_data.philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
