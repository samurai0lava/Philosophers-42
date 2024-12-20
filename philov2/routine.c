/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:40:29 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/21 10:38:57 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	forks_change(t_philo *philo, int *first_fork, int *second_fork)
{
	int	left_fork;
	int	right_fork;
	int	tmp;

	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	if (philo->id % 2 == 0)
	{
		*first_fork = right_fork;
		*second_fork = left_fork;
	}
	else
	{
		*first_fork = left_fork;
		*second_fork = right_fork;
	}
	if (*first_fork > *second_fork)
	{
		tmp = *first_fork;
		*first_fork = *second_fork;
		*second_fork = tmp;
	}
}

void	acquire_forks(t_philo *philo, int *first_fork, int *second_fork)
{
    forks_change(philo, first_fork, second_fork);
    if (pthread_mutex_lock(&philo->data.forks[*first_fork]) != 0)
        return ;
    printf_state(philo, PHILO_FORK);
    if (pthread_mutex_lock(&philo->data.forks[*second_fork]) != 0)
        return ;
    printf_state(philo, PHILO_FORK);
}

void eat(t_philo *philo)
{
    int first_fork;
    int second_fork;

    acquire_forks(philo, &first_fork, &second_fork);
    
    pthread_mutex_lock(&philo->data.dead);
    if (philo->data.is_dead)
    {
        pthread_mutex_unlock(&philo->data.dead);
        pthread_mutex_unlock(&philo->data.forks[second_fork]);
        pthread_mutex_unlock(&philo->data.forks[first_fork]);
        return;
    }
    pthread_mutex_unlock(&philo->data.dead);
    pthread_mutex_lock(&philo->data.state_mutex);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->data.state_mutex);
    
    pthread_mutex_lock(&philo->data.eats);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->data.eats);
    
    printf_state(philo, PHILO_EAT);
    precise_usleep(philo->philo_data.time_to_eat);
    
    pthread_mutex_unlock(&philo->data.forks[second_fork]);
    pthread_mutex_unlock(&philo->data.forks[first_fork]);
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        precise_usleep(philo->philo_data.time_to_eat / 2);

    while (dead_philo(philo) == 0)
    {
        eat(philo);
        sleep_and_think(philo);
    }
    return (NULL);
}

void sleep_and_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->data.dead);
    if (philo->data.is_dead)
    {
        pthread_mutex_unlock(&philo->data.dead);
        return;
    }
    pthread_mutex_unlock(&philo->data.dead);

    printf_state(philo, PHILO_SLEEP);
    precise_usleep(philo->philo_data.time_to_sleep);

    pthread_mutex_lock(&philo->data.dead);
    if (philo->data.is_dead)
    {
        pthread_mutex_unlock(&philo->data.dead);
        return;
    }
    pthread_mutex_unlock(&philo->data.dead);

    printf_state(philo, PHILO_THINK);
}

