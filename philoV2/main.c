#include "philo.h"

int creath_thread(t_philo *philos)
{
    int i;
    int check;

    i = 0;
    while(philos[0].philo_data.numb_of_philos > i)
    {
        check = pthread_create(&philos[i].shared_data.philos[i], NULL, &routine, &philos[i]);
        if (check != 0)
            return (1);
        i++;
    }
    return (0);
}

int create_thread_monitor(t_philo *philos)
{
    int check;

    check = pthread_create(&philos[0].shared_data.philos[philos[0].philo_data.numb_of_philos], NULL, &monitor, philos);
    if (check != 0)
        return (1);
    return (0);
}

int init_mutexes(t_philo *philos)
{
    int i;

    philos[0].shared_data.forks = malloc(sizeof(pthread_mutex_t) * philos[0].philo_data.numb_of_philos);
    philos[0].shared_data.print = malloc(sizeof(pthread_mutex_t));
    philos[0].shared_data.dead = malloc(sizeof(pthread_mutex_t));
    philos[0].shared_data.philos = malloc(sizeof(pthread_t) * (philos[0].philo_data.numb_of_philos + 1));
    
    if (!philos[0].shared_data.forks || !philos[0].shared_data.print || 
        !philos[0].shared_data.dead || !philos[0].shared_data.philos)
        return (1);
    
    i = 0;
    while (i < philos[0].philo_data.numb_of_philos)
    {
        if (pthread_mutex_init(&philos[0].shared_data.forks[i], NULL))
            return (1);
        i++;
    }
    if (pthread_mutex_init(philos[0].shared_data.print, NULL) || 
        pthread_mutex_init(philos[0].shared_data.dead, NULL) ||
        pthread_mutex_init(&philos[0].shared_data.state_mutex, NULL)) // Initialize new mutex
        return (1);
    return (0);
}

void init_philosophers(t_philo *philos)
{
    int i;
    
    i = 0;
    while (i < philos[0].philo_data.numb_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].eat_count = 0;
        philos[i].last_meal_time = get_time();
        philos[i].shared_data = philos[0].shared_data;
        philos[i].philo_data = philos[0].philo_data;
        philos[i].shared_data.is_dead = 0;
        philos[i].shared_data.is_eating = 0;
        philos[i].shared_data.is_sleeping = 0;
        philos[i].shared_data.is_thinking = 0;
        philos[i].shared_data.left_fork = i;
        philos[i].shared_data.right_fork = (i + 1) % philos[0].philo_data.numb_of_philos;
        philos[i].shared_data.start_time = get_time();
        i++;
    }
}

void cleanup(t_philo *philos)
{
    int i;
    
    i = 0;
    while (i < philos[0].philo_data.numb_of_philos)
    {
        pthread_mutex_destroy(&philos[0].shared_data.forks[i]);
        i++;
    }
    pthread_mutex_destroy(philos[0].shared_data.print);
    pthread_mutex_destroy(philos[0].shared_data.dead);
    pthread_mutex_destroy(&philos[0].shared_data.state_mutex); // Destroy new mutex
    free(philos[0].shared_data.forks);
    free(philos[0].shared_data.print);
    free(philos[0].shared_data.dead);
    free(philos[0].shared_data.philos);
}

void start_simulation(t_philo *philos)
{
    long long   start_time; 
    int         i;

    i = 0;
    start_time = get_time();
    philos[0].last_meal_time = start_time;
    if (creath_thread(philos) != 0)
    {
        philos[0].shared_data.is_dead = 1;
        return;
    }
    if (create_thread_monitor(philos) != 0)
    {
        philos[0].shared_data.is_dead = 1;
        return;
    }
    while(i <= philos[0].philo_data.numb_of_philos)
    {
        if (pthread_join(philos[0].shared_data.philos[i], NULL) != 0)
        {
            philos[0].shared_data.is_dead = 1;
            break;
        }
        i++;
    }
}

int main(int ac , char **av)
{
    t_philo *philos;

    if (ac != 5 && ac != 6)
        return (return_error(ARG_FAILS));

    philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    if (!philos)
        return (1);

    if (parse_input(philos, ac, av) != 0)
    {
        free(philos);
        return (1);
    }

    if (init_mutexes(philos) != 0)
    {
        cleanup(philos);
        free(philos);
        return (1);
    }

    init_philosophers(philos);
    start_simulation(philos);
    cleanup(philos);
    free(philos);
    return (0);
}