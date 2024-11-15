/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:26:45 by iouhssei          #+#    #+#             */
/*   Updated: 2024/11/15 10:29:19 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_fork(t_philo *philo)
{
    if (philo->left_fork < philo->right_fork)
    {
        pthread_mutex_lock(&philo->forks[philo->left_fork]);
        pthread_mutex_lock(&philo->mutex);
        if (!philo->is_dead)
            printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
        pthread_mutex_unlock(&philo->mutex);

        pthread_mutex_lock(&philo->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->mutex);
        if (!philo->is_dead)
            printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
        pthread_mutex_unlock(&philo->mutex);
    }
    else
    {
        pthread_mutex_lock(&philo->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->mutex);
        if (!philo->is_dead)
            printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
        pthread_mutex_unlock(&philo->mutex);

        pthread_mutex_lock(&philo->forks[philo->left_fork]);
        pthread_mutex_lock(&philo->mutex);
        if (!philo->is_dead)
            printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
        pthread_mutex_unlock(&philo->mutex);
    }
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex);
    philo->last_eat = get_time();
    philo->is_eating = 1;
    if (!philo->is_dead)
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_EAT);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->mutex);

    precise_usleep(philo->time_to_eat * 1000);

    pthread_mutex_lock(&philo->mutex);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->mutex);

    pthread_mutex_unlock(&philo->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->forks[philo->right_fork]);
}

void think(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex);
    if (!philo->is_dead)
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_THINK);
    pthread_mutex_unlock(&philo->mutex);
}

void sleep_and_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex);
    if (!philo->is_dead)
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_SLEEP);
    pthread_mutex_unlock(&philo->mutex);

    precise_usleep(philo->time_to_sleep * 1000);
    think(philo);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    pthread_mutex_lock(&philo->mutex);
    philo->last_eat = get_time();
    pthread_mutex_unlock(&philo->mutex);
    if (philo->id % 2)
        precise_usleep(philo->time_to_eat * 100);

    while (1)
    {
        pthread_mutex_lock(&philo->mutex);
        if (philo->is_dead)
        {
            pthread_mutex_unlock(&philo->mutex);
            break;
        }
        pthread_mutex_unlock(&philo->mutex);
        take_fork(philo);
        eat(philo);
        sleep_and_think(philo);
    }
    return (NULL);
}

int check_is_death(t_philo *philo)
{
    unsigned long long current_time = get_time();

    pthread_mutex_lock(&philo->mutex);
    if (!philo->is_eating && 
        (current_time - philo->last_eat) > (unsigned long long)philo->time_to_die)
    {
        philo->is_dead = 1;
        printf("%llu %d %s\n", current_time - philo->start_time, philo->id, PHILO_DEAD);
        pthread_mutex_unlock(&philo->mutex);
        return 1;
    }
    pthread_mutex_unlock(&philo->mutex);
    return 0;
}


void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    int i;
    int all_ate_enough;
    int status;

    while (1)
    {
        all_ate_enough = 1;
        for (i = 0; i < philos[0].number_of_philosophers; i++)
        {
            status = check_is_death(&philos[i]);
            printf("status: %d\n", status);
            if (status == 1)
                return (NULL);
            if (philos[0].number_of_eats > 0)
            {
                pthread_mutex_lock(&philos[i].mutex);
                if (philos[i].eat_count < philos[0].number_of_eats)
                    all_ate_enough = 0;
                pthread_mutex_unlock(&philos[i].mutex);
            }
        }
        if (all_ate_enough)
            break;
        usleep(500);
    }
    return NULL;
}
