/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:06 by ilyass            #+#    #+#             */
/*   Updated: 2024/11/06 15:58:27 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int check_num(char **str)
{
	int i;
	int j;

	if (str == NULL)
		return (0);
	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_isdigit(str[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_philo *return_error(char *str)
{
	printf(MAGENTA "%s" RESET, str);
	return (NULL);
}

static void init_philo(t_philo *philo, char **av)
{
	philo->number_of_philosophers = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->number_of_forks = philo->number_of_philosophers;
}

t_philo *parse_input(int ac, char **av)
{
	t_philo *philo;
	int number_of_philosophers;

	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1 || ft_atoi(av[4]) < 1 || (ac == 6 && ft_atoi(av[5]) < 1))
			return (return_error(ARG_FAILS));
		if (check_num(av) == 0)
			return (return_error(ARG_FAILS));
		number_of_philosophers = ft_atoi(av[1]);
		if (number_of_philosophers == 0)
			return (return_error(ARG_FAILS));
		philo = malloc(sizeof(t_philo) * number_of_philosophers);
		if (!philo)
			return (NULL);
		init_philo(philo, av);
		if (av[5] != NULL)
			philo->number_of_eats = ft_atoi(av[5]);
		else
			philo->number_of_eats = -1;
		return (philo);
	}
	else
		return (return_error(ARG_FAILS));
}
