/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:16 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/29 20:09:08 by samurai0lav      ###   ########.fr       */
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
    int         i;
    int         all_alive;

	i = 0;
	all_alive = 0;
	philos = NULL;
	
	init_struct(philos);
    if (parse_input(ac, av, philos) != 0)
        return (1);
    threads = create_threads(philos);
    if (threads == NULL)
        return (1);
    philos->start_time = get_time();
    all_alive = 1;
    while (all_alive)
    {
        for (i = 0; i < philos->number_of_philosophers; i++)
        {
            pthread_mutex_lock(&philos[i].mutex);
            if (check_is_death(&philos[i]))
            {
                all_alive = 0;
                pthread_mutex_unlock(&philos[i].mutex);
                break;
            }
            if (philos[i].eat_count >= philos[i].number_of_eats && philos[i].number_of_eats != -1)
            {
                all_alive = 0;
                pthread_mutex_unlock(&philos[i].mutex);
                break;
            }
            pthread_mutex_unlock(&philos[i].mutex);
        }
        usleep(1000);  // Sleep for 1ms to reduce CPU usage
    }

    // Wait for all threads to finish
    for (i = 0; i < philos->number_of_philosophers; i++)
        pthread_join(threads[i], NULL);

    free_all(philos, threads);
    return (0);
}
