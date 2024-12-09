/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:40:28 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/09 19:15:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_philo_all *philo)
{
	int	i;

	philo->philos = malloc(sizeof(t_philo) * philo->philo_data.numb_of_philos);
	if (!philo->philos)
		return (1);
	philo->data.forks = malloc(sizeof(pthread_mutex_t)
			* philo->philo_data.numb_of_philos);
	if (!philo->data.forks)
	{
		free(philo->philos);
		return (1);
	}
	i = 0;
	while (i < philo->philo_data.numb_of_philos)
	{
		if (pthread_mutex_init(&philo->data.forks[i], NULL) != 0)
		{
			free(philo->philos);
			free(philo->data.forks);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&philo->data.print, NULL) != 0
		|| pthread_mutex_init(&philo->data.dead, NULL) != 0
		|| pthread_mutex_init(&philo->data.state_mutex, NULL) != 0
		|| pthread_mutex_init(&philo->data.eats, NULL) != 0)
	{
		free(philo->philos);
		free(philo->data.forks);
		return (1);
	}
	return (0);
}

void	init_philosophers(t_philo_all *philos)
{
	int	i;

	i = 0;
	while (i < philos->philo_data.numb_of_philos)
	{
		philos->philos[i].id = i + 1;
		philos->philos[i].eat_count = 0;
		philos->philos[i].last_meal_time = get_time();
		philos->data.is_dead = 0;
		philos->philos[i].left_fork = i;
		philos->philos[i].right_fork = (i + 1)
			% philos[0].philo_data.numb_of_philos;
		philos->data.start_time = get_time();
		philos->data.is_eating = 0;
		i++;
	}
}

void	handle_one_philo(t_philo_all *philos)
{
	precise_usleep(philos->philo_data.time_to_die);
	printf("%lld %d died\n", get_time() - philos->data.start_time,
		philos->philos->id);
}

int	start_simulation(t_philo_all *philos)
{
	long long	start_time;

	// int 		i;
	start_time = get_time();
	philos->philos->last_meal_time = start_time;
	if (create_thread_monitor(philos) != 0)
		return (1);
	if (creath_thread(philos) != 0)
		return (1);
	if (pthread_join(philos->data.monitor_thread, NULL) != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo_all	*philos;
	int			numbofphilos;

	if (ac != 5 && ac != 6)
		return (return_error(ARG_FAILS));
	numbofphilos = parse_num_of_philos(av[1]);
	if (numbofphilos == -1)
		return (return_error(ARG_FAILS));
	philos = malloc(sizeof(t_philo_all));
	if (!philos)
		return (1);
	if (parse_input(philos, ac, av) != 0)
		return (free(philos), 1);
	if (init_mutexes(philos) != 0)
		return (cleanup(philos), 1);
	init_philosophers(philos);
	if (philos->philo_data.numb_of_philos == 1)
		return (handle_one_philo(philos), cleanup(philos), 0);
	if (start_simulation(philos) != 0)
		return (cleanup(philos), 1);
	cleanup(philos);
	return (0);
}
