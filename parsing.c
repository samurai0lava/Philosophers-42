/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:06 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/18 18:48:03 by ilyass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parse_input(int ac, char **av, t_philo *philo)
{
	//test is numeric 
	//test if the minumm number of argumanets required
	//test max int i guess (to look it up)
	//convert the input into integer
	//check overflow
	//asign it to the struct (i need an other function)
	if(ac == 4 || ac == 5)
	{
		if(ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1 || (ac == 5 && ft_atoi(av[4]) < 1))
		{
			printf(RED ARG_FAILS RESET);
			return (1);
		}
		philo->number_of_philosophers = ft_atoi(av[1]);
		philo->time_to_die = ft_atoi(av[2]);
		philo->time_to_eat = ft_atoi(av[3]);
		philo->time_to_sleep = ft_atoi(av[4]);
		if(ac == 5)
			philo->number_of_eats = ft_atoi(av[5]);
		else
			philo->number_of_eats = -1;
		return (0);		
	}
	else
	{
		printf(ORANGE ARG_FAILS RESET);
		return (1);
	}
}