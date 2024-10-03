/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:24 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/30 11:15:49 by samurai0lav      ###   ########.fr       */
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

void *monitor_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        pthread_mutex_lock(&philo->mutex);
        if (check_is_death(philo))
        {
            pthread_mutex_unlock(&philo->mutex);
            return NULL;
        }
        if (philo->eat_count >= philo->number_of_eats && philo->number_of_eats != -1)
        {
            pthread_mutex_unlock(&philo->mutex);
            return NULL;
        }
        pthread_mutex_unlock(&philo->mutex);
        usleep(1000); // Sleep for 1ms to reduce CPU usage
    }
    return NULL;
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        take_fork(philo);
        eat(philo);
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
