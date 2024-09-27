/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:24 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/27 17:27:29 by ilyass           ###   ########.fr       */
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
int check_is_death(t_philo *philo)
{
	__U64_TYPE current_time;

	current_time = get_time();
	if (current_time - philo->last_eat > philo->time_to_die)
	{
		philo->is_dead = 1;
		printf("%d %s", philo->id, PHILO_DEAD);
		return (1); //<-- the operation has ended
	}	
}


void *monitor_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	
}
void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(1)
	{
		take_fork(arg);
		eat(arg);
		sleep_and_think(arg);
		if(philo->is_dead)
			break;
	}	
}
