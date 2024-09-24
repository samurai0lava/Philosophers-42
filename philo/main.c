/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:16 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/23 11:08:29 by ilyass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_philo *philo)
{
	philo->id = 0;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->eat_count = 0;
	philo->last_eat = 0;
	philo->is_eating = 0;
	philo->is_sleeping = 0;
	philo->is_thinking = 0;
	philo->is_dead = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->number_of_eats = 0;
	philo->number_of_philosophers = 0;
	philo->number_of_forks = 0;
}

static void	print_struct(t_philo *philo)
{
	printf("id: %d\n", philo->id);
	printf("left_fork: %d\n", philo->left_fork);
	printf("right_fork: %d\n", philo->right_fork);
	printf("eat_count: %d\n", philo->eat_count);
	printf("last_eat: %d\n", philo->last_eat);
	printf("is_eating: %d\n", philo->is_eating);
	printf("is_sleeping: %d\n", philo->is_sleeping);
	printf("is_thinking: %d\n", philo->is_thinking);
	printf("is_dead: %d\n", philo->is_dead);
	printf("time_to_die: %d\n", philo->time_to_die);
	printf("time_to_eat: %d\n", philo->time_to_eat);
	printf("time_to_sleep: %d\n", philo->time_to_sleep);
	printf("number_of_eats: %d\n", philo->number_of_eats);
	printf("number_of_philosophers: %d\n", philo->number_of_philosophers);
}

static pthread_t	*create_threads(t_philo *philo)
{
	int			i;
	pthread_t	*philos;

	i = 0;
	philos = (pthread_t *)malloc(sizeof(pthread_t)
			* philo->number_of_philosophers);
	if (philos == NULL)
	{
		write(2, "malloc : error\n", 16);
		return (NULL);
	}
	while (i < philo->number_of_philosophers)
	{
		if (pthread_create(&philos[i], NULL, &routine, philo) != 0)
		{
			write(2, "pthread_create error\n", 22);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

static int	start_simulation(t_philo *philo, pthread_t *threads)
{
		

	return (0);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	pthread_t	*threads;

	init_struct(&philo);
	parse_input(ac, av, &philo);
	threads = create_threads(&philo);
	if (threads == NULL)
		return (1);
	if (start_simulation(&philo, threads) != 0)
		return (1);
	print_struct(&philo);
	return (0);
}