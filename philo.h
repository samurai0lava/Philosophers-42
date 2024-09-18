#ifndef PHILO_H
#define PHILO_H

//includes
# include <pthread.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
#include <errno.h>

//PHILO MESSAGES
#define PHILO_EAT "is eating\n"
#define PHILO_SLEEP "is sleeping\n"
#define PHILO_THINK "is thinking\n"
#define PHILO_FORK "has taken a fork\n"
#define PHILO_DEAD "died\n"
#define ARG_FAILS "Usage : number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

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
    int id;
    int left_fork;
    int right_fork;
    int eat_count;
    int last_eat;
    int is_eating;
    int is_sleeping;
    int is_thinking;
    int is_dead;
    pthread_mutex_t *forks;
    pthread_mutex_t *print;
    pthread_mutex_t *eat;
}               t_philo;

//Functions prototypes
int parse_input(int ac, char **av, t_philo *philo);

#endif