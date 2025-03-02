/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:00:57 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/30 20:51:30 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_individual_eats(t_philo *philos)
{
	int	finished_eating;
	int	i;

	finished_eating = 0;
	i = 0;
	while (i < philos[0].philo_data.numb_of_philos)
	{
		pthread_mutex_lock(&philos[0].data.state_mutex);
		pthread_mutex_lock(philos[0].data.eats);
		if (philos[i].eat_count >= philos[0].philo_data.number_of_eats)
			finished_eating++;
		pthread_mutex_unlock(philos[0].data.eats);
		pthread_mutex_unlock(&philos[0].data.state_mutex);
		i++;
	}
	return (finished_eating);
}

static int	check_and_update_dead_state(t_philo *philos, int finished_eating)
{
	int	should_die;

	should_die = 0;
	pthread_mutex_lock(&philos[0].data.state_mutex);
	if (finished_eating >= philos[0].philo_data.numb_of_philos)
		should_die = 1;
	pthread_mutex_unlock(&philos[0].data.state_mutex);
	return (should_die);
}

int	check_if_all_ate(t_philo *philos)
{
	int	finished_eating;

	if (!philos)
		return (-1);
	if (pthread_mutex_lock(&philos[0].data.state_mutex) != 0)
		return (-1);
	if (philos[0].philo_data.number_of_eats == -1)
	{
		if (pthread_mutex_unlock(&philos[0].data.state_mutex) != 0)
			return (-1);
		return (0);
	}
	else
	{
		if (pthread_mutex_unlock(&philos[0].data.state_mutex) != 0)
			return (-1);
		finished_eating = check_individual_eats(philos);
		return (check_and_update_dead_state(philos, finished_eating));
	}
}

void	printf_state(t_philo *philo, char *state)
{
	if (pthread_mutex_lock(&philo[0].data.state_mutex))
		return ;
	if (ft_strncmp(state, PHILO_DEAD, sizeof(PHILO_DEAD)) == 0
		|| !check_is_dead(philo))
	{
		if (pthread_mutex_lock(philo[0].data.print))
			return ;
		printf("%lld %d %s", get_time() - philo->data.start_time, philo->id,
			state);
		if (pthread_mutex_unlock(philo[0].data.print))
			return ;
	}
	if (pthread_mutex_unlock(&philo[0].data.state_mutex))
		return ;
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
