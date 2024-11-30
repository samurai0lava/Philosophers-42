/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:36:16 by iouhssei          #+#    #+#             */
/*   Updated: 2024/11/30 14:38:52 by iouhssei         ###   ########.fr       */
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

void wait_and_cleanup(t_philo *philos, pthread_t *threads)
{
    int i;

    if (philos == NULL || threads == NULL)
        return;

    // Join philosopher threads
    for (i = 0; i < philos[0].philo_data.numb_of_philos; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
            printf("Error: Failed to join thread %d\n", i);
    }
    // Join monitor thread
    if (pthread_join(philos[0].shared_data.monitor_thread, NULL) != 0)
        printf("Error: Failed to join monitor thread\n");
    // Synchronize cleanup to avoid data races
    // pthread_mutex_lock(&philos[0].shared_data.cleanup_mutex);
    cleanup(philos);
    // pthread_mutex_unlock(&philos[0].shared_data.cleanup_mutex);
}



void cleanup(t_philo *philos)
{
    // int i;

    if (philos == NULL)
        return;
    // i = 0;
	// while(i < philos[0].philo_data.numb_of_philos)
	// {
	// 	if (pthread_mutex_unlock(&philos[0].shared_data.forks[i]) != 0)
	// 	{
	// 		printf("failed to unlock : the forks mutex %d\n", i);
	// 		return ;
	// 	}
	// 	i++;
	// }
	// i = 0;
		// pthread_mutex_unlock(&philos[0].shared_data.forks[0]);
    // while (i < philos[0].philo_data.numb_of_philos)
    // {
	// 	// pthread_mutex_unlock(&philos[0].shared_data.forks[i]);
    //     if (pthread_mutex_destroy(&philos[0].shared_data.forks[i]) != 0)
	// 	{
	// 		// printf("%d\n", gettid());
	// 		printf("failed to destroy : the forks mutex %d\n", i);
	// 		return ;
	// 	}
    //     i++;
    // }
	
    if (pthread_mutex_destroy(philos[0].shared_data.print) != 0)
	{
		printf("failed to destroy : the print mutex\n");
		return ;
	}
    pthread_mutex_destroy(philos[0].shared_data.dead);
    pthread_mutex_destroy(&philos[0].shared_data.state_mutex);
    pthread_mutex_destroy(&philos[0].shared_data.eats);
    free(philos[0].shared_data.forks);
    free(philos[0].shared_data.print);
    free(philos[0].shared_data.dead);
    free(philos[0].shared_data.philos);
    free(philos);
}

int create_thread_monitor(t_philo *philos)
{
	int check;

	check = pthread_create(&philos[0].shared_data.monitor_thread, NULL,
			&monitor, philos);
	if (check != 0)
		return (1);
	return (0);
}

int creath_thread(t_philo *philos)
{
	int	i;
	int check;

	i = 0;
	while(philos[0].philo_data.numb_of_philos > i)
	{
		check = pthread_create(&philos[i].shared_data.philos[i],
				NULL, &routine, &philos[i]);
		if (check != 0)
			return (1);
		pthread_detach(philos[i].shared_data.philos[i]);
		i++;
	}
	return (0);
}
