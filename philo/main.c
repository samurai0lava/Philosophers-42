/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:16 by ilyass            #+#    #+#             */
/*   Updated: 2024/10/18 18:14:22 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_struct(t_philo *philo)
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

int init_mutex(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->number_of_forks)
    {
        if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
        {
            write(2, "pthread_mutex_init error\n", 26);
            return (1);
        }
        i++;
    }
    return (0);
}

pthread_t *create_threads(t_philo *philos)
{
    int i;
    pthread_t *threads;

    threads = (pthread_t *)malloc(sizeof(pthread_t) * philos[0].number_of_philosophers);
    if (threads == NULL)
    {
        write(2, "malloc : error\n", 16);
        return (NULL);
    }
    i = 0;
    while (i < philos[0].number_of_philosophers)
    {
        if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
        {
            write(2, "pthread_create error\n", 22);
            return (NULL);
        }
        i++;
    }
    return (threads);
}

static void handle_one_p(t_philo *philos)
{
    usleep(philos->time_to_die * 1000);
    printf("%d %s", 1, PHILO_DEAD);
    free(philos);
}

int main(int ac, char **av)
{
    t_philo *philos;
    pthread_t *threads;
    pthread_mutex_t *forks;
    int i;
    __U64_TYPE start_time;
    pthread_t monitor;

    philos = malloc(sizeof(t_philo));
    if (!philos)
        return (1);
    if (parse_input(ac, av, philos) != 0)
        return (free(philos), 1);
    if (philos->number_of_philosophers == 1)
		return (handle_one_p(philos), 0);
	philos = realloc(philos, sizeof(t_philo) * philos->number_of_philosophers);
    forks = malloc(sizeof(pthread_mutex_t) * philos->number_of_philosophers);
    threads = malloc(sizeof(pthread_t) * philos->number_of_philosophers);
    if (!forks || !threads || !philos)
		return (free_all(philos, threads, forks), 1);
    i = 0;
    while (i < philos->number_of_philosophers)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
            return (free_all(philos, threads, forks), 1);
        i++;
    }
    start_time = get_time();
    i = 0;
    while (i < philos->number_of_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].left_fork = i;
        philos[i].right_fork = (i + 1) % philos->number_of_philosophers;
        philos[i].forks = forks;
        philos[i].time_to_die = philos->time_to_die;
        philos[i].time_to_eat = philos->time_to_eat;
        philos[i].time_to_sleep = philos->time_to_sleep;
        philos[i].number_of_eats = philos->number_of_eats;
        philos[i].number_of_philosophers = philos->number_of_philosophers;
        philos[i].last_eat = start_time;
        philos[i].start_time = start_time;
        philos[i].eat_count = 0;
        philos[i].is_dead = 0;
        if (pthread_mutex_init(&philos[i].mutex, NULL) != 0)
            return (free_all(philos, threads, forks), 1);
        i++;
    }
    philos->start_time = get_time();
    threads = create_threads(philos);
    if (!threads)
        return (free_all(philos, threads, forks), 1);
    if (pthread_create(&monitor, NULL, &monitor_routine, philos) != 0)
        return (free_all(philos, threads, forks), 1);
    i = 0;
    while (i < philos->number_of_philosophers)
    {
        if (pthread_join(threads[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_join(monitor, NULL) != 0)
        return (1);
    free_all(philos, threads, forks);
    return (0);
}