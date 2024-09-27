/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:24 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/27 10:35:05 by ilyass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_fork(t_philo *philo)
{

}
void eat(t_philo *philo)
{

}
void sleep_and_think(t_philo *philo)
{

}

void *monitor_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
}
void *routine(void *arg)
{

	while(1)
	{
		take_fork(arg);
		eat(arg);
		sleep_and_think(arg);
	}	
}