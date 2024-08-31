#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>


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


#endif