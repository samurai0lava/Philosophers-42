/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:57:24 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/24 10:13:23 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_philo_death(t_philo *philo, long long current_time)
{
    pthread_mutex_lock(&philo->data.state_mutex);
    if (current_time - philo->last_meal_time > philo->philo_data.time_to_die && philo->data.is_eating == 0)
    {        
        pthread_mutex_lock(&philo->data.dead);
        *philo->data.is_dead = 1;
        pthread_mutex_unlock(&philo->data.dead);
        printf_state(philo, PHILO_DEAD);
        pthread_mutex_unlock(&philo->data.state_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data.state_mutex);
    return (0);
}


void *monitor(void *arg)
{
    t_philo *philos;
    int      i;
    long long current_time;

    philos = (t_philo *)arg;
    while (1)
    {
        i = 0;
        while (i < philos[0].philo_data.numb_of_philos)
        {
            current_time = get_time();
            if (check_philo_death(&philos[i], current_time) == 1 || check_if_all_ate(philos))
                return(NULL) ;
            i++;
        }
        usleep(1000);
    }
    return (arg);
}

int check_is_dead(t_philo *philos)
{
    pthread_mutex_lock(&philos->data.dead);
    if(*philos->data.is_dead == 1)
    {
        pthread_mutex_unlock(&philos->data.dead);
        return (1);
    }
    pthread_mutex_unlock(&philos->data.dead);
    return (0);
}

int pthread_mutex_philo(t_philo *philos)
{
    int i;

    if (pthread_mutex_init(&philos->data.print, NULL) != 0 || pthread_mutex_init(&philos->data.dead, NULL) != 0 || pthread_mutex_init(&philos->data.state_mutex, NULL) != 0 || pthread_mutex_init(&philos->data.eats, NULL) != 0)
        return (1);

    i = 0;
    while (i < philos[0].philo_data.numb_of_philos)
    {
        if (pthread_mutex_init(&philos->data.forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&philos->data.forks[i]);
            pthread_mutex_destroy(&philos->data.print);
            pthread_mutex_destroy(&philos->data.dead);
            pthread_mutex_destroy(&philos->data.state_mutex);
            pthread_mutex_destroy(&philos->data.eats);
            return (1);
        }
        i++;
    }
    return (0);
}