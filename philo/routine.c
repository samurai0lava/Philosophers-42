/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:40:29 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/27 14:04:36 by iouhssei         ###   ########.fr       */
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

void	eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	acquire_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->data.state_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data.state_mutex);
	pthread_mutex_lock(&philo->data.eats);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data.eats);
	printf_state(philo, PHILO_EAT);
	precise_usleep(philo->philo_data.time_to_eat);
	pthread_mutex_unlock(&philo->data.forks[first_fork]);
	pthread_mutex_unlock(&philo->data.forks[second_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->philo_data.time_to_eat / 2);
	while (check_is_dead(philo) == 0)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (arg);
}

void	sleep_and_think(t_philo *philo)
{
	printf_state(philo, PHILO_SLEEP);
	precise_usleep(philo->philo_data.time_to_sleep);
	printf_state(philo, PHILO_THINK);
}
