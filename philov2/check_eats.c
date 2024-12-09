/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:00:57 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/09 19:10:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_individual_eats(t_philo_all *philos, int *finished_eating)
{
	int	i;

	i = 0;
	while (i < philos->philo_data.numb_of_philos)
	{
		pthread_mutex_lock(&philos->data.eats);
		if (philos->philos[i].eat_count >= philos->philo_data.number_of_eats)
			(*finished_eating)++;
		pthread_mutex_unlock(&philos->data.eats);
		i++;
	}
	return (*finished_eating);
}

static int	check_and_update_dead_state(t_philo_all *philos, int finished_eating)
{
	if (philos->philo_data.numb_of_philos == finished_eating)
	{
		pthread_mutex_lock(&philos->data.dead);
		philos->data.is_dead = 1;
		pthread_mutex_unlock(&philos->data.dead);
		return (1);
	}
	return (0);
}

int	check_if_all_ate(t_philo_all *philos)
{
	int	finished_eating;

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

void	init_philo_parsing(t_philo_all *philo, char **av)
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

void	printf_state(t_philo_all *philo, int id, char *state)
{
    if (pthread_mutex_lock(&philo->data.print) != 0)
        return ;
    printf("%lld %d %s", get_time() - philo->data.start_time, id, state);
    if (pthread_mutex_unlock(&philo->data.print) != 0)
        return ;
}
