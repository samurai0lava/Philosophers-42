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
    pthread_mutex_t *print;
    pthread_mutex_t *dead;
    pthread_mutex_t state_mutex; // New mutex for shared states
    pthread_t *philos;
    pthread_t *monitor_thread;
    long long start_time;
    int is_dead;
    int left_fork;
    int right_fork;
} t_shared_data;

typedef struct s_philo
{
	int     		id;
	int     		eat_count;
	long long		last_meal_time;
	t_data  		philo_data;
	t_shared_data   shared_data;
}   t_philo;


int creath_thread(t_philo *philo);
int create_thread_monitor(t_philo *philo);
int init_mutexes(t_philo *philo);
void init_philosophers(t_philo *philo);
void cleanup(t_philo *philo);
int start_simulation(t_philo *philo);
int	ft_atoi(const char *str);
int ft_isdigit(int c);
int check_num(char **str);
int parse_input(t_philo *philo, int ac, char **av);
void take_fork(t_philo *philo);
void eat(t_philo *philo);
void sleep_and_think(t_philo *philo);
void *routine(void *arg);
void *monitor(void *arg);
long long get_time(void);
int precise_usleep(long usec);
int return_error(char *str);
int parse_num_of_philos(char *av);

#endif