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

typedef struct s_data
{
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int numb_of_philos;
	int number_of_eats;
}   t_data;

typedef struct s_shared_data
{
	pthread_mutex_t *forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	int             is_dead;
	int             is_eating;
	int             is_sleeping;
	int             is_thinking;
	pthread_t	   *philos;
	int				left_fork;
	int				right_fork;
}   t_shared_data;

typedef struct s_philo
{
	int     		id;
	int     		eat_count;
	long long		last_meal_time;   // Add this field
	t_data  		philo_data;
	t_shared_data   shared_data;

}   t_philo;

// Add these function prototypes
long long	get_time(void);

int precise_usleep(long usec);

#endif