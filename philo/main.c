/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:40:28 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/30 20:24:25 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_philo *philo)
{
	int	i;

	philo[0].data.forks = malloc(sizeof(pthread_mutex_t)
			* philo->philo_data.numb_of_philos);
	if (!philo[0].data.forks)
		return (1);
	philo[0].data.is_dead = malloc(sizeof(int));
	if (!philo[0].data.is_dead)
		return (free(philo[0].data.forks), 1);
	philo[0].data.dead = malloc(sizeof(pthread_mutex_t));
	if (!philo[0].data.dead)
		return (free(philo[0].data.is_dead), free(philo[0].data.forks), 1);
	philo[0].data.eats = malloc(sizeof(pthread_mutex_t));
	if (!philo[0].data.eats)
		return (free(philo[0].data.is_dead), free(philo[0].data.forks),
			free(philo[0].data.dead), 1);
	*philo[0].data.is_dead = 0;
	i = 0;
	while (i < philo->philo_data.numb_of_philos)
	{
		if (pthread_mutex_init(&philo[0].data.forks[i], NULL) != 0)
			return (free(philo[0].data.is_dead), free(philo[0].data.forks), 1);
		i++;
	}
	if (pthread_mutex_init(&philo[0].data.print, NULL) != 0
		|| pthread_mutex_init(philo[0].data.dead, NULL) != 0
		|| pthread_mutex_init(&philo[0].data.state_mutex, NULL) != 0
		|| pthread_mutex_init(philo[0].data.eats, NULL) != 0)
		return (free(philo[0].data.is_dead), free(philo[0].data.forks), 1);
	return (0);
}

void	init_philosophers(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->philo_data.numb_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_meal_time = get_time();
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % philos[0].philo_data.numb_of_philos;
		philos[0].data.start_time = get_time();
		philos[0].data.is_eating = 0;
		philos[i].data = philos[0].data;
		philos[i].philo_data = philos[0].philo_data;
		i++;
	}
}

void	handle_one_philo(t_philo *philos)
{
	precise_usleep(philos->philo_data.time_to_die);
	printf("%lld %d died\n", get_time() - philos->data.start_time, philos->id);
}

int	start_simulation(t_philo *philos)
{
	int	i;

	philos->data.start_time = get_time();
	if (create_thread_monitor(philos) != 0)
		return (1);
	if (creath_thread(philos) != 0)
		return (1);
	i = 0;
	while (philos->philo_data.numb_of_philos > i)
	{
		if (pthread_join(philos[i].philo_thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(philos[0].data.monitor_thread, NULL) != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	int		numbofphilos;

	if (ac != 5 && ac != 6)
		return (return_error(ARG_FAILS));
	numbofphilos = parse_num_of_philos(av[1]);
	if (numbofphilos == -1)
		return (return_error(ARG_FAILS));
	philos = malloc(sizeof(t_philo) * numbofphilos);
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
