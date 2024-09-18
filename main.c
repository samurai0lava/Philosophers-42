/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:16 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/18 18:50:45 by ilyass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_struct(t_philo *philo)
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
    philo->forks = NULL;
    philo->print = NULL;
    philo->eat = NULL;
}
// void *philo_routine()
// {
//     printf("lets_goooooooooooooooooo\n");
//     return (NULL);
// }
// void *philo_routine1()
// {
//     printf("wesh abatal\n");
//     return (NULL);
// }

int main(int ac , char **av)
{
    t_philo philo;
    // pthread_t *thread1;
    // pthread_t *thread2;

    // thread2 = (pthread_t *)malloc(sizeof(pthread_t));
    // if (thread2 == NULL)
    // {
    //     perror("malloc");
    //     return (1);
    // }
    // thread1 = (pthread_t *)malloc(sizeof(pthread_t));
    // if (thread1 == NULL)
    // {
	// 	perror("malloc");
    //     return (1);
    // }
    // if (pthread_create(thread1, NULL, &philo_routine, NULL) != 0)
    //     return 1;
    // if (pthread_create(thread2, NULL, &philo_routine1, NULL) != 0)
    //     return (1);
    // pthread_join(*thread1, NULL);
    // pthread_join(*thread2, NULL);
    // free(thread1);
    // free(thread2);
	
	init_struct(&philo);
	parse_input(ac, av, &philo);
    return (0);
}