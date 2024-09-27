/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:37:41 by iouhssei          #+#    #+#             */
/*   Updated: 2024/09/27 17:19:30 by ilyass           ###   ########.fr       */
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
		return_value = return_value * 10 + (*str - 48) * sign;
		str++;
	}
	return (return_value);
}

int join_threads(pthread_t *threads, int nof)
{
	int	i;
	i = 0;
	while (i < nof)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			write(2, "pthread_join error\n", 20);
			return (1);
		}
		i++;
	}
	return (0);
}

void free_all(t_philo *philo, pthread_t *threads)
{
	
}