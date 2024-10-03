/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:16 by ilyass            #+#    #+#             */
/*   Updated: 2024/10/03 17:27:16 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_philo *philo)
{
	philo->id = 0;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->eat_count = 0;
	philo->last_eat = 0;
	philo->is_eating = 0;
	philo->is_sleeping = 0;
	philo->is_thinking = 0;
	philo->is_dead = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->number_of_eats = 0;
	philo->number_of_philosophers = 0;
	philo->number_of_forks = 0;
	philo->start_time = 0;
}
// static void	print_struct(t_philo *philo)
// {
// 	printf("id: %d\n", philo->id);
// 	printf("left_fork: %d\n", philo->left_fork);
// 	printf("right_fork: %d\n", philo->right_fork);
// 	printf("eat_count: %d\n", philo->eat_count);
// 	printf("last_eat: %d\n", philo->last_eat);
// 	printf("is_eating: %d\n", philo->is_eating);
// 	printf("is_sleeping: %d\n", philo->is_sleeping);
// 	printf("is_thinking: %d\n", philo->is_thinking);
// 	printf("is_dead: %d\n", philo->is_dead);
// 	printf("time_to_die: %d\n", philo->time_to_die);
// 	printf("time_to_eat: %d\n", philo->time_to_eat);
// 	printf("time_to_sleep: %d\n", philo->time_to_sleep);
// 	printf("number_of_eats: %d\n", philo->number_of_eats);
// 	printf("number_of_philosophers: %d\n", philo->number_of_philosophers);
// }

int create_philos(t_philo *philo)
{
    int i;
    t_philo *philos;

    philos = malloc(sizeof(t_philo) * philo->number_of_philosophers);
    if (!philos)
        return (1);
    i = 0;
    while (i < philo->number_of_philosophers)
    {
        philos[i] = *philo;
        philos[i].id = i + 1;
        philos[i].left_fork = i;
        philos[i].right_fork = (i + 1) % philo->number_of_philosophers;
        philos[i].last_eat = get_time();
        i++;
    }
    philo = philos;
    return (0);
}
int init_mutex(t_philo *philo)
{
	int i;
	i = 0;
	while (i < philo->number_of_forks)
	{
		if (pthread_mutex_init(&philo->mutex, NULL) != 0)
		{
			write(2, "pthread_mutex_init error\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}

pthread_t	*create_threads(t_philo *philo)
{
	int			i;
	pthread_t	*philos;
	i = 0;
	philos = (pthread_t *)malloc(sizeof(pthread_t)
			* philo->number_of_philosophers);
	if (philos == NULL)
	{
		write(2, "malloc : error\n", 16);
		return (NULL);
	}
	while (i < philo->number_of_philosophers)
	{
		if (pthread_create(&philos[i], NULL, &routine, philo) != 0)
		{
			write(2, "pthread_create error\n", 22);
			return (NULL);
		}
		i++;
	}
	return (philos);
}


int handle_one_philo(t_philo *philo)
{
	pthread_t	*thread;
	thread = create_threads(philo);
	if (thread == NULL)
		return (1);
	if (pthread_create(thread, NULL, &routine, philo) != 0)
	{
		write(2, "pthread_create error\n", 22);
		return (1);
	}
	if (pthread_join(*thread, NULL) != 0)
	{
		write(2, "pthread_join error\n", 20);
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
    t_philo     *philos;
    pthread_t   *threads;
    pthread_mutex_t *forks;
    int         i;

    philos = malloc(sizeof(t_philo));
    if (!philos)
        return (1);

    if (parse_input(ac, av, philos) != 0)
    {
        free(philos);
        return (1);
    }

    philos = realloc(philos, sizeof(t_philo) * philos->number_of_philosophers);
    forks = malloc(sizeof(pthread_mutex_t) * philos->number_of_philosophers);
    threads = malloc(sizeof(pthread_t) * philos->number_of_philosophers);

    if (!philos || !forks || !threads)
    {
        // Handle allocation error
        free(philos);
        free(forks);
        free(threads);
        return (1);
    }

    for (i = 0; i < philos->number_of_philosophers; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
        philos[i].id = i + 1;
        philos[i].left_fork = i;
        philos[i].right_fork = (i + 1) % philos->number_of_philosophers;
        philos[i].forks = forks;
        // Copy other necessary fields from the parsed input
        philos[i].time_to_die = philos->time_to_die;
        philos[i].time_to_eat = philos->time_to_eat;
        philos[i].time_to_sleep = philos->time_to_sleep;
        philos[i].number_of_eats = philos->number_of_eats;
        philos[i].number_of_philosophers = philos->number_of_philosophers;
    }

    philos->start_time = get_time();

    for (i = 0; i < philos->number_of_philosophers; i++)
    {
        if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
        {
            // Handle thread creation error
            return (1);
        }
    }

    // Monitor thread
    pthread_t monitor;
    if (pthread_create(&monitor, NULL, &monitor_routine, philos) != 0)
    {
        // Handle monitor thread creation error
        return (1);
    }

    // Join threads
    for (i = 0; i < philos->number_of_philosophers; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_join(monitor, NULL);

    // Cleanup
    for (i = 0; i < philos->number_of_philosophers; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }
    free(philos);
    free(forks);
    free(threads);

    return (0);
}
