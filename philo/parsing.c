/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:40:00 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/08 18:37:13 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long int	return_value;

	sign = 1;
	return_value = 0;
	while (*str && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((return_value * 10 + (*str - '0')) > INT_MAX)
			return (-1);
		if ((return_value * 10 + (*str - '0')) * sign < INT_MIN)
			return (-1);
		return_value = return_value * 10 + (*str - '0');
		str++;
	}
	return (return_value * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_num(char **str)
{
	int	i;
	int	j;

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

int	parse_input(t_philo *philo, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (check_num(av) == 0)
			return (return_error(ARG_FAILS));
		if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1
			|| ft_atoi(av[4]) < 1 || (ac == 6 && ft_atoi(av[5]) < 1))
			return (return_error(ARG_FAILS));
		init_philo_parsing(philo, av);
		if (philo->philo_data.numb_of_philos == 0)
			return (return_error(ARG_FAILS));
	}
	else
		return (return_error(ARG_FAILS));
	return (0);
}

int	parse_num_of_philos(char *av)
{
	int	numb_of_philos;
	int	i;

	i = 0;
	if (ft_atoi(av) < 1)
		return (-1);
	while (av[i])
	{
		if (ft_isdigit(av[i]) == 0)
			return (-1);
		i++;
	}
	numb_of_philos = ft_atoi(av);
	if (numb_of_philos > 200)
		return (-1);
	return (numb_of_philos);
}
