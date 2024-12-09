/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:40:29 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/09 19:10:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	forks_change(t_philo_all *philo, int *first_fork, int *second_fork)
{
	int	left_fork;
	int	right_fork;
	int	tmp;

	left_fork = philo->philos->left_fork;
	right_fork = philo->philos->right_fork;
	if (philo->philos->id % 2 == 0)
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

void	acquire_forks(t_philo_all *philo, int *first_fork, int *second_fork)
{
    forks_change(philo, first_fork, second_fork);
    if (pthread_mutex_lock(&philo->data.forks[*first_fork]) != 0)
        return ;
    printf_state(philo, philo->philos->id, PHILO_FORK);
    if (pthread_mutex_lock(&philo->data.forks[*second_fork]) != 0)
        return ;
    printf_state(philo, philo->philos->id, PHILO_FORK);
}

void	eat(t_philo_all *philo)
{
    int	first_fork;
    int	second_fork;

    acquire_forks(philo, &first_fork, &second_fork);
    if (pthread_mutex_lock(&philo->data.state_mutex) != 0)
        return ;
    philo->philos->last_meal_time = get_time();
    if (pthread_mutex_unlock(&philo->data.state_mutex) != 0)
        return ;
    pthread_mutex_lock(&philo->data.eats);
    philo->philos->eat_count++;
    if (pthread_mutex_unlock(&philo->data.eats) != 0)
        return ;
    printf_state(philo, philo->philos->id, PHILO_EAT);
    precise_usleep(philo->philo_data.time_to_eat);
    if (pthread_mutex_unlock(&philo->data.forks[second_fork]) != 0)
        return ;
    if (pthread_mutex_unlock(&philo->data.forks[first_fork]) != 0)
        return ;
}

void	sleep_and_think(t_philo_all *philo)
{
    printf_state(philo, philo->philos->id, PHILO_SLEEP);
    precise_usleep(philo->philo_data.time_to_sleep);
    printf_state(philo, philo->philos->id, PHILO_THINK);
}

void	*routine(void *arg)
{
	t_philo_all	*philo;

	philo = (t_philo_all *)arg;
	if (philo->philos->id % 2 == 0)
		precise_usleep(10);
	while (dead_philo(philo) == 0)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
