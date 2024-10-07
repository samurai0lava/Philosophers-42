/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:06 by ilyass            #+#    #+#             */
/*   Updated: 2024/10/06 18:49:04 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(int ac, char **av, t_philo *philo)
{
	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1
			|| ft_atoi(av[4]) < 1 || (ac == 6 && ft_atoi(av[5]) < 1))
		{
			printf(MAGENTA ARG_FAILS RESET);
			return (1);
		}
		philo->number_of_philosophers = ft_atoi(av[1]);
		if(philo->number_of_philosophers == 0)
		{
			printf(MAGENTA ARG_FAILS RESET);
			return (1);
		}
		philo->time_to_die = ft_atoi(av[2]);
		philo->time_to_eat = ft_atoi(av[3]);
		philo->time_to_sleep = ft_atoi(av[4]);
		if (av[5] != NULL)
			philo->number_of_eats = ft_atoi(av[5]);
		else
			philo->number_of_eats = -1;
		return (0);
	}
	else
	{
		printf(MAGENTA ARG_FAILS RESET);
		return (1);
	}
}
