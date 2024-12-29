/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:57:24 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/29 13:25:58 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_occured(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data.dead) != 0)
		return (-1);
	(*philo->data.is_dead) = 1; //<--- DATA RACE HERE
	if (pthread_mutex_unlock(&philo->data.dead) != 0)
		return (-1);
	return (0);
}

int	check_philo_death(t_philo *philo, long long current_time)
{
	if (pthread_mutex_lock(&philo->data.state_mutex))
		return (-1);
	if (current_time - philo->last_meal_time > philo->philo_data.time_to_die
		&& philo->data.is_eating == 0)
	{
		if (pthread_mutex_unlock(&philo->data.state_mutex))
			return (-1);
		return (1);
	}
	if (pthread_mutex_unlock(&philo->data.state_mutex))
		return (-1);
	return (0);
}

static int check_philosopher_status(t_philo *philo)
{
    long long current_time;

    current_time = get_time();
    if (check_philo_death(philo, current_time) == 1)
    {
        printf_state(philo, PHILO_DEAD);
        if (death_occured(philo) != 0)
            return (-1);
        return (1);
    }
    if (check_if_all_ate(philo))
    {
        if (death_occured(philo) != 0)
            return (-1);
        return (1);
    }
    return (0);
}

void *monitor(void *arg)
{
    t_philo *philos;
    int     i;
    int     status;

    philos = (t_philo *)arg;
    while (1)
    {
        i = 0;
        while (i < philos[0].philo_data.numb_of_philos)
        {
            status = check_philosopher_status(&philos[i]);
            if (status != 0)
                return (NULL);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

int	check_is_dead(t_philo *philos)
{
	int	status;

	if (pthread_mutex_lock(&philos->data.dead) != 0)
		return (-1);
	status = (*philos->data.is_dead);
	if (pthread_mutex_unlock(&philos->data.dead) != 0)
		return (-1);

	return (status);
}

int	pthread_mutex_philo(t_philo *philos)
{
	int	i;

	if (pthread_mutex_init(&philos->data.print, NULL) != 0
		|| pthread_mutex_init(&philos->data.dead, NULL) != 0
		|| pthread_mutex_init(&philos->data.state_mutex, NULL) != 0
		|| pthread_mutex_init(&philos->data.eats, NULL) != 0)
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
