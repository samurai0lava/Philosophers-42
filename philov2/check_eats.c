/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:00:57 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/06 10:23:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_individual_eats(t_philo *philos, int *finished_eating)
{
	int	i;

	i = 0;
	while (i < philos[0].philo_data.numb_of_philos)
	{
		pthread_mutex_lock(&philos[i].shared_data.eats);
		if (philos[i].eat_count >= philos[i].philo_data.number_of_eats)
			(*finished_eating)++;
		pthread_mutex_unlock(&philos[i].shared_data.eats);
		i++;
	}
	return (*finished_eating);
}

static int	check_and_update_dead_state(t_philo *philos, int finished_eating)
{
	if (philos[0].philo_data.numb_of_philos == finished_eating)
	{
		pthread_mutex_lock(philos[0].shared_data.dead);
		philos[0].shared_data.is_dead = 1;
		pthread_mutex_unlock(philos[0].shared_data.dead);
		return (1);
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	finished_eating;

	pthread_mutex_lock(&philos[0].shared_data.state_mutex);
	if (philos[0].philo_data.number_of_eats == -1)
	{
		pthread_mutex_unlock(&philos[0].shared_data.state_mutex);
		return (0);
	}
	finished_eating = 0;
	finished_eating = check_individual_eats(philos, &finished_eating);
	if (check_and_update_dead_state(philos, finished_eating))
	{
		pthread_mutex_unlock(&philos[0].shared_data.state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos[0].shared_data.state_mutex);
	return (0);
}

void	init_philo_parsing(t_philo *philo, char **av)
{
	philo->philo_data.numb_of_philos = ft_atoi(av[1]);
	philo->philo_data.time_to_die = ft_atoi(av[2]);
	philo->philo_data.time_to_eat = ft_atoi(av[3]);
	philo->philo_data.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->philo_data.number_of_eats = ft_atoi(av[5]);
	else
		philo->philo_data.number_of_eats = -1;
}

void	printf_state(t_philo *philo, char *state)
{
	printf("%lld %d %s", get_time() - philo->shared_data.start_time, philo->id,
		state);
}