/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:00:57 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/24 10:07:55 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_individual_eats(t_philo *philos, int *finished_eating)
{
	int i;

	i = 0;
	while (i < philos->philo_data.numb_of_philos)
	{
		pthread_mutex_lock(&philos->data.eats);
		if (philos[i].eat_count >= philos->philo_data.number_of_eats)
		{
			pthread_mutex_lock(&philos->data.state_mutex);
			(*finished_eating)++;
			pthread_mutex_unlock(&philos->data.state_mutex);
		}
		pthread_mutex_unlock(&philos->data.eats);
		i++;
	}
	return (*finished_eating);
}

static int	check_and_update_dead_state(t_philo *philos, int finished_eating)
{
	pthread_mutex_lock(&philos->data.state_mutex);
	if (philos->philo_data.numb_of_philos == finished_eating)
	{
		pthread_mutex_lock(&philos->data.dead);
		*philos->data.is_dead = 1;
		pthread_mutex_unlock(&philos->data.dead);
		pthread_mutex_unlock(&philos->data.state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->data.state_mutex);
	return (0);
}

int check_if_all_ate(t_philo *philos)
{
	int finished_eating;

	pthread_mutex_lock(&philos->data.state_mutex);
	if (philos[0].philo_data.number_of_eats == -1)
	{
		pthread_mutex_unlock(&philos->data.state_mutex);
		return (0);
	}
	finished_eating = 0;
	finished_eating = check_individual_eats(philos, &finished_eating);
	if (check_and_update_dead_state(philos, finished_eating))
	{
		pthread_mutex_unlock(&philos->data.state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->data.state_mutex);
	return (0);
}



int dead_philo(t_philo *philo)
{

	pthread_mutex_lock(&philo->data.state_mutex);
	if(*philo->data.is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data.state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data.state_mutex);
	return (0);
}

void printf_state(t_philo *philo, char *state)
{
	if (pthread_mutex_lock(&philo->data.print) != 0)
		return;
	printf("%lld %d %s", get_time() - philo->data.start_time, philo->id, state);
	if (pthread_mutex_unlock(&philo->data.print) != 0)
		return;
}
void init_philo_parsing(t_philo *philo, char **av)
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