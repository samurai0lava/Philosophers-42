/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:57:24 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/09 19:11:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo_all	*philos;

	philos = (t_philo_all *)arg;
	while (1)
	{
		pthread_mutex_lock(&philos->data.dead);
		if (philos->data.is_dead == 1)
		{
			pthread_mutex_unlock(&philos->data.dead);
			return (NULL);
		}
		pthread_mutex_unlock(&philos->data.dead);
		if (check_if_all_ate(philos) == 1 || check_is_dead(philos) == 1)
			return (NULL);
	}
	return (arg);
}

int	check_is_dead(t_philo_all *philos)
{
    int			i;
    long long	current_time;

    i = 0;
    while (i < philos->philo_data.numb_of_philos)
    {
        current_time = get_time();
        pthread_mutex_lock(&philos->data.state_mutex);
        pthread_mutex_lock(&philos->data.dead);
        if (current_time
            - philos->philos[i].last_meal_time > philos->philo_data.time_to_die
            && philos->data.is_eating == 0)
        {
            printf_state(philos, philos->philos[i].id, PHILO_DEAD);
            philos->data.is_dead = 1;
            pthread_mutex_unlock(&philos->data.dead);
            pthread_mutex_unlock(&philos->data.state_mutex);
            return (1);
        }
        pthread_mutex_unlock(&philos->data.dead);
        pthread_mutex_unlock(&philos->data.state_mutex);
        i++;
    }
    return (0);
}

int	dead_philo(t_philo_all *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->data.state_mutex);
	is_dead = philo->data.is_dead;
	pthread_mutex_unlock(&philo->data.state_mutex);
	return (is_dead);
}

int	pthread_mutex_philo(t_philo_all *philos)
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
			return (1);
		}
		i++;
	}
	return (0);
}

