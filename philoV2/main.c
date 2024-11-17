#include "philo.h"

int creath_thread(t_philo *philo)
{
    int i;
    int check;

    i = 0;
    while(philo->philo_data.numb_of_philos > i)
    {
        check = pthread_create(&philo->shared_data.philos[i], NULL, &routine, philo);
        if (check != 0)
            return (1);
        i++;
    }
    return (0);
}

int create_thread_monitor(t_philo *philo)
{
    int check;

    check = pthread_create(&philo->shared_data.philos[philo->philo_data.numb_of_philos], NULL, &monitor, philo);
    if (check != 0)
        return (1);
    return (0);
}

int init_mutexes(t_philo *philo)
{
    int i;
    
    philo->shared_data.forks = malloc(sizeof(pthread_mutex_t) * philo->philo_data.numb_of_philos);
    philo->shared_data.print = malloc(sizeof(pthread_mutex_t));
    philo->shared_data.dead = malloc(sizeof(pthread_mutex_t));
    philo->shared_data.philos = malloc(sizeof(pthread_t) * (philo->philo_data.numb_of_philos + 1));
    
    if (!philo->shared_data.forks || !philo->shared_data.print || 
        !philo->shared_data.dead || !philo->shared_data.philos)
        return (1);
    
    i = 0;
    while (i < philo->philo_data.numb_of_philos)
    {
        if (pthread_mutex_init(&philo->shared_data.forks[i], NULL))
            return (1);
        i++;
    }
    if (pthread_mutex_init(philo->shared_data.print, NULL) || 
        pthread_mutex_init(philo->shared_data.dead, NULL))
        return (1);
    return (0);
}

void init_philosophers(t_philo *philo)
{
    int i;
    
    for (i = 0; i < philo->philo_data.numb_of_philos; i++)
    {
        philo->id = i + 1;
        philo->eat_count = 0;
        philo->last_meal_time = get_time();
        philo->shared_data.is_dead = 0;
        philo->shared_data.is_eating = 0;
        philo->shared_data.is_sleeping = 0;
        philo->shared_data.is_thinking = 0;
        philo->shared_data.left_fork = i;
        philo->shared_data.right_fork = (i + 1) % philo->philo_data.numb_of_philos;
    }
}

void cleanup(t_philo *philo)
{
    int i;
    
    for (i = 0; i < philo->philo_data.numb_of_philos; i++)
        pthread_mutex_destroy(&philo->shared_data.forks[i]);
    pthread_mutex_destroy(philo->shared_data.print);
    pthread_mutex_destroy(philo->shared_data.dead);
    free(philo->shared_data.forks);
    free(philo->shared_data.print);
    free(philo->shared_data.dead);
    free(philo->shared_data.philos);
}

void start_simulation(t_philo *philo)
{
    // Set start time for all philosophers
    long long start_time = get_time();
    philo->last_meal_time = start_time;
    
    // Create philosopher threads
    if (creath_thread(philo) != 0)
    {
        philo->shared_data.is_dead = 1;
        return;
    }
    
    // Create monitor thread
    if (create_thread_monitor(philo) != 0)
    {
        philo->shared_data.is_dead = 1;
        return;
    }
    
    // Wait for all threads to finish
    int i;
    for (i = 0; i <= philo->philo_data.numb_of_philos; i++)
    {
        if (pthread_join(philo->shared_data.philos[i], NULL) != 0)
        {
            philo->shared_data.is_dead = 1;
            break;
        }
    }
}

int main(int ac , char **av)
{
    t_philo philo;

    if (parse_input(&philo, ac, av) != 0)
        return (1);
    if (init_mutexes(&philo) != 0)
    {
        cleanup(&philo);
        return (1);
    }
    init_philosophers(&philo);
    start_simulation(&philo);
    cleanup(&philo);
    return (0);
}