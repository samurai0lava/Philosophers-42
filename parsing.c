/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:06 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/18 18:17:07 by ilyass           ###   ########.fr       */
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
		
	}
	else
	{
		printf(ORANGE ARG_FAILS RESET);
		return (1);
	}
}