/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:37:10 by iouhssei          #+#    #+#             */
/*   Updated: 2024/12/09 19:11:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// includes
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// PHILO MESSAGES
# define PHILO_EAT "is eating\n"
# define PHILO_SLEEP "is sleeping\n"
# define PHILO_THINK "is thinking\n"
# define PHILO_FORK "has taken a fork\n"
# define PHILO_DEAD "died\n"
# define ARG_FAILS "Philo Usage : num_of_philos die eat sleep [eats]\n"

// colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define ORANGE "\033[0;36m"
# define RESET "\033[0m"

typedef struct s_data
{
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				numb_of_philos;
	int				number_of_eats;
}					t_data;

typedef struct s_shared_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	eats;
	long long		start_time;
	int				is_dead;
	int				is_eating;
	pthread_t		monitor_thread;
}					t_shared_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long long		last_meal_time;
	pthread_t		philo_thread;
}					t_philo;

typedef struct s_philo_all
{
	t_philo			*philos;
	t_data			philo_data;
	t_shared_data	data;
}	t_philo_all;

int					creath_thread(t_philo_all *philo);
int					create_thread_monitor(t_philo_all *philo);
int					init_mutexes(t_philo_all *philo);
void				init_philosophers(t_philo_all *philo);
void				cleanup(t_philo_all *philo);
int					start_simulation(t_philo_all *philo);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					check_num(char **str);
int					parse_input(t_philo_all *philo, int ac, char **av);
void				eat(t_philo_all *philo);
void				sleep_and_think(t_philo_all *philo);
void				*routine(void *arg);
void				*monitor(void *arg);
long long			get_time(void);
int					precise_usleep(long usec);
int					return_error(char *str);
int					parse_num_of_philos(char *av);
int					dead_philo(t_philo_all *philo);
int					check_if_all_ate(t_philo_all *philos);
int					check_is_dead(t_philo_all *philos);
void	printf_state(t_philo_all *philo, int id, char *state);
int					pthread_mutex_philo(t_philo_all *philos);
void				init_philo_parsing(t_philo_all *philo, char **av);
void				acquire_forks(t_philo_all *philo, int *first_fork,
						int *second_fork);

#endif
