/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyass <ilyass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:16 by ilyass            #+#    #+#             */
/*   Updated: 2024/09/21 11:58:24 by ilyass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_struct(t_philo *philo)
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
static void  print_struct(t_philo *philo)
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
    print_struct(&philo);
    return (0);
}