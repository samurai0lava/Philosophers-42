/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:40:29 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/01 20:45:56 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_state(t_philo *philo, char *state)
{
	printf("%lld %d %s",
		get_time() - philo->shared_data.start_time, philo->id, state);
}

static void forks_change(t_philo *philo, int *first_fork, int *second_fork)
{
    int left_fork = philo->shared_data.left_fork;
    int right_fork = philo->shared_data.right_fork;

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
        int tmp = *first_fork;
        *first_fork = *second_fork;
        *second_fork = tmp;
    }
}

void	eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;
	
	pthread_mutex_lock(&philo->shared_data.state_mutex);
	forks_change(philo, &first_fork, &second_fork);
	pthread_mutex_unlock(&philo->shared_data.state_mutex);
	pthread_mutex_lock(&philo->shared_data.forks[first_fork]);
	printf_state(philo, PHILO_FORK);
	pthread_mutex_lock(&philo->shared_data.forks[second_fork]);
	printf_state(philo, PHILO_FORK);
	pthread_mutex_lock(&philo->shared_data.state_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->shared_data.state_mutex);
	pthread_mutex_lock(&philo->shared_data.eats);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->shared_data.eats);
	pthread_mutex_lock(philo->shared_data.print);
	printf_state(philo, PHILO_EAT);
	pthread_mutex_unlock(philo->shared_data.print);
	precise_usleep(philo->philo_data.time_to_eat);
	pthread_mutex_unlock(&philo->shared_data.forks[second_fork]);
	pthread_mutex_unlock(&philo->shared_data.forks[first_fork]);
}

void	sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_data.print);
	printf_state(philo, PHILO_SLEEP);
	pthread_mutex_unlock(philo->shared_data.print);
	precise_usleep(philo->philo_data.time_to_sleep);
	pthread_mutex_lock(philo->shared_data.print);
	printf_state(philo, PHILO_THINK);
	pthread_mutex_unlock(philo->shared_data.print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

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
