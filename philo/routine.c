/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:24 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/22 19:13:07 by ilyass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void creating_multiple_threads(t_philo philo)
// {
// 	int i;

// 	i = 0;
// 	while(i < philo.number_of_philosophers)
// 	{
// 		pthread_create(&philo.threads[i], NULL, routine, &philo);
// 		i++;
// 	}
// }


void is_eating(t_philo *philo)
{
	philo->is_eating = 1;
	printf(GREEN "%d " PHILO_EAT RESET, philo->id);
	philo->eat_count++;
	philo->last_eat = get_time();
	philo->is_eating = 0;
}

void is_sleeping(t_philo *philo)
{
	philo->is_sleeping = 1;
	printf(YELLOW "%d " PHILO_SLEEP RESET, philo->id);
	precise_usleep(philo->time_to_sleep);
	philo->is_sleeping = 0;
}

void is_thinking(t_philo *philo)
{
	philo->is_thinking = 1;
	printf(BLUE "%d " PHILO_THINK RESET, philo->id);
	philo->is_thinking = 0;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex);
	printf("Hello from the thread\n");
	printf("Thread number: %d\n", philo->id);
	philo->id++;
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

// int	main(void) 
// {
// 	t_philo *philo;
// 	pthread_t thread[5];
// 	int i;
// 	// int *thread_num;

// 	philo = malloc(sizeof(t_philo));
// 	if (!philo)
// 	{
// 		perror("malloc");
// 		return (1);
// 	}
// 	// philo->id = 0;
// 	pthread_mutex_init(&philo->mutex, NULL);
// 	i = 0;
// 	while (i < 5)
// 	{
// 		if (pthread_create(&thread[i], NULL, &routine, philo) != 0)
// 		{
// 			perror("pthread_create");
// 			return (1);
// 		}
// 		philo->id = i;
// 		printf(BLUE "Thread %d created\n" RESET, i);
// 		// pthread_detach(thread[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 5)
// 	{
// 		if (pthread_join(thread[i], NULL) != 0)
// 		{
// 			perror("pthread_join");
// 			return (1);
// 		}
// 		printf(RED "Thread %d joined\n" RESET, i);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&philo->mutex);
// 	free(philo);
// 	return (0);
// }