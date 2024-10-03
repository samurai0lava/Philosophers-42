/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:24 by ilyass            #+#    #+#             */
/*   Updated: 2024/10/03 17:27:31 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex);
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
    pthread_mutex_unlock(&philo->mutex);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex);
    philo->is_eating = 1;
    philo->last_eat = get_time();
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_EAT);
    pthread_mutex_unlock(&philo->mutex);

    precise_usleep(philo->time_to_eat * 1000);

    pthread_mutex_lock(&philo->mutex);
    philo->is_eating = 0;
    philo->eat_count++;
    pthread_mutex_unlock(&philo->mutex);
}

void sleep_and_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex);
    philo->is_sleeping = 1;
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_SLEEP);
    pthread_mutex_unlock(&philo->mutex);

    precise_usleep(philo->time_to_sleep * 1000);

    pthread_mutex_lock(&philo->mutex);
    philo->is_sleeping = 0;
    philo->is_thinking = 1;
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_THINK);
    pthread_mutex_unlock(&philo->mutex);
}
int check_is_death(t_philo *philo)
{
    __U64_TYPE current_time;

    current_time = get_time();
    if ((current_time - (unsigned long long)(philo->last_eat)) > (unsigned long long)philo->time_to_die)
    {
        philo->is_dead = 1;
        printf("%d %s", philo->id, PHILO_DEAD);
        return (1); //<-- the operation has ended
    }
    return (0);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        // Odd philosophers take left fork first, even take right fork first
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(&philo->forks[philo->right_fork]);
            pthread_mutex_lock(&philo->forks[philo->left_fork]);
        }
        else
        {
            pthread_mutex_lock(&philo->forks[philo->left_fork]);
            pthread_mutex_lock(&philo->forks[philo->right_fork]);
        }

        eat(philo);

        pthread_mutex_unlock(&philo->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->forks[philo->right_fork]);

        sleep_and_think(philo);

        pthread_mutex_lock(&philo->mutex);
        if (philo->is_dead || (philo->eat_count >= philo->number_of_eats && philo->number_of_eats != -1))
        {
            pthread_mutex_unlock(&philo->mutex);
            break;
        }
        pthread_mutex_unlock(&philo->mutex);
    }
    return NULL;
}

void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    int i;
    int all_alive = 1;

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
        usleep(1000);
    }
    return NULL;
}
