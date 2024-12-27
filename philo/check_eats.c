/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:00:57 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/27 13:50:44 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_individual_eats(t_philo *philos)
{
	int	i;
	int	finished_eating;
	int	current_eat_count;

	i = 0;
	finished_eating = 0;
	pthread_mutex_lock(&philos[0].data.state_mutex);
	while (i < philos[0].philo_data.numb_of_philos)
	{
		pthread_mutex_lock(&philos[0].data.eats);
		current_eat_count = philos[i].eat_count;
		pthread_mutex_unlock(&philos[0].data.eats);
		if (current_eat_count >= philos[0].philo_data.number_of_eats)
			finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&philos[0].data.state_mutex);
	return (finished_eating);
}

static int	check_and_update_dead_state(t_philo *philos, int finished_eating)
{
	int	should_die;

	should_die = 0;
	pthread_mutex_lock(&philos[0].data.state_mutex);
	pthread_mutex_lock(&philos[0].data.dead);
	if (finished_eating >= philos[0].philo_data.numb_of_philos)
	{
		death_occured(philos);
		should_die = 1;
	}
	pthread_mutex_unlock(&philos[0].data.dead);
	pthread_mutex_unlock(&philos[0].data.state_mutex);
	return (should_die);
}

int	check_if_all_ate(t_philo *philos)
{
	int	finished_eating;

	pthread_mutex_lock(&philos[0].data.state_mutex);
	if (philos[0].philo_data.number_of_eats == -1)
	{
		pthread_mutex_unlock(&philos[0].data.state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philos[0].data.state_mutex);
	finished_eating = check_individual_eats(philos);
	return (check_and_update_dead_state(philos, finished_eating));
}

void	printf_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data.print);
	if (ft_strncmp(state, PHILO_DEAD, sizeof(PHILO_DEAD)) == 0
		|| !check_is_dead(philo))
		printf("%lld %d %s", get_time() - philo->data.start_time, philo->id,
			state);
	pthread_mutex_unlock(&philo->data.print);
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
