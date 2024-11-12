/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:26:45 by iouhssei          #+#    #+#             */
/*   Updated: 2024/11/11 10:27:44 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_fork(t_philo *philo)
{
    if (philo->left_fork < philo->right_fork)
    {
        pthread_mutex_lock(&philo->forks[philo->left_fork]);
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
        pthread_mutex_lock(&philo->forks[philo->right_fork]);
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
    }
    else
    {
        pthread_mutex_lock(&philo->forks[philo->right_fork]);
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
        pthread_mutex_lock(&philo->forks[philo->left_fork]);
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
    }
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex);
    philo->is_eating = 1;
    philo->last_eat = get_time() - philo->start_time;
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_EAT);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->mutex);
    
    precise_usleep(philo->time_to_eat * 1000);
    
    pthread_mutex_lock(&philo->mutex);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->mutex);
    
    pthread_mutex_unlock(&philo->forks[philo->right_fork]);
    pthread_mutex_unlock(&philo->forks[philo->left_fork]);
}

void think(t_philo *philo)
{
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_THINK);
}

void sleep_and_think(t_philo *philo)
{
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_SLEEP);
    precise_usleep(philo->time_to_sleep);
    think(philo);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    if (philo->id % 2)
        precise_usleep(1000);
    
    while (1)
    {
        pthread_mutex_lock(&philo->mutex);
        if (philo->is_dead || (philo->number_of_eats != -1 && 
            philo->eat_count >= philo->number_of_eats))
        {
            pthread_mutex_unlock(&philo->mutex);
            break;
        }
        pthread_mutex_unlock(&philo->mutex);
        
        take_fork(philo);
        eat(philo);
        sleep_and_think(philo);
    }
    return NULL;
}

int check_is_death(t_philo *philo)
{
    unsigned long long current_time;
    
    pthread_mutex_lock(&philo->mutex);
    current_time = get_time() - philo->start_time;
    if (!philo->is_eating && 
        (current_time - philo->last_eat) > (unsigned long long)philo->time_to_die)
    {
        philo->is_dead = 1;
        printf("%llu %d %s", current_time, philo->id, PHILO_DEAD);
        pthread_mutex_unlock(&philo->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->mutex);
    return (0);
}

void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    int i;
    int finished_eating = 0;
    
    while (1)
    {
        finished_eating = 0;
        i = -1;
        while (++i < philos->number_of_philosophers)
        {
            pthread_mutex_lock(&philos[i].mutex);
            if (philos[i].number_of_eats != -1 && 
                philos[i].eat_count >= philos[i].number_of_eats)
                finished_eating++;
            if (!philos[i].is_eating && 
                (get_time() - philos[i].start_time - philos[i].last_eat) > 
                (unsigned long long)philos[i].time_to_die)
            {
                printf("%llu %d %s", get_time() - philos[i].start_time, 
                       philos[i].id, PHILO_DEAD);
                philos[i].is_dead = 1;
                pthread_mutex_unlock(&philos[i].mutex);
                return NULL;
            }
            pthread_mutex_unlock(&philos[i].mutex);
        }
        if (finished_eating == philos->number_of_philosophers)
            return NULL;
        usleep(1000);
    }
    return NULL;
}