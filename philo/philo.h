/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:33 by ilyass            #+#    #+#             */
/*   Updated: 2024/10/10 18:50:20 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

//includes
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>
# include <limits.h>

//PHILO MESSAGES
#define PHILO_EAT "is eating\n"
#define PHILO_SLEEP "is sleeping\n"
#define PHILO_THINK "is thinking\n"
#define PHILO_FORK "has taken a fork\n"
#define PHILO_DEAD "died\n"
#define ARG_FAILS "Philosophers Usage : number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

//colors
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define ORANGE "\033[0;36m"
#define RESET "\033[0m"

//struct for the philosophers
typedef struct s_philo
{
    int				id;
    int 			left_fork;
    int 			right_fork;
    int 			eat_count;
    int 			last_eat;
    int 			is_eating;
    int 			is_sleeping;
    int 			is_thinking;
    int 			is_dead;
    int 			time_to_die;
    int 			time_to_eat;
    int				time_to_sleep;
    int				number_of_eats;
    int				number_of_philosophers;
    int				number_of_forks;
    unsigned long long	start_time;
    pthread_mutex_t mutex;
    pthread_mutex_t *forks;
}               t_philo;

//Functions prototypes
int					parse_input(int ac, char **av, t_philo *philo);
unsigned long long	get_time(void);
void				init_struct(t_philo *philo);
int					precise_usleep(long usec);
int 				ft_atoi(const char *str);
int					init_mutex(t_philo *philo);
void				take_fork(t_philo *philo);
void				eat(t_philo *philo);
void				sleep_and_think(t_philo *philo);
void				*routine(void *arg);
pthread_t			*create_threads(t_philo *philo);
int					join_threads(pthread_t *threads, int nof);
int					start_simulation(t_philo *philo, pthread_t *threads);
int                 check_is_death(t_philo *philo);
void                *monitor_routine(void *arg);
void                free_all(t_philo *philo, pthread_t *threads);

#endif