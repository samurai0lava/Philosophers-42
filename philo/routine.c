#include "philo.h"


// Take forks implementation
void take_fork(t_philo *philo)
{
    // Always take lower numbered fork first to prevent deadlock
    if (philo->left_fork < philo->right_fork)
    {
        pthread_mutex_lock(&philo->forks[philo->left_fork]);
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
        pthread_mutex_lock(&philo->forks[philo->right_fork]);
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
    }
    else
    {
        pthread_mutex_lock(&philo->forks[philo->right_fork]);
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
        pthread_mutex_lock(&philo->forks[philo->left_fork]);
        printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_FORK);
    }
}

// Eating implementation
void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex);
    philo->is_eating = 1;
    philo->last_eat = get_time() - philo->start_time;
    pthread_mutex_unlock(&philo->mutex);
    
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_EAT);
    precise_usleep(philo->time_to_eat);
    
    pthread_mutex_lock(&philo->mutex);
    philo->eat_count++;
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->mutex);
    
    // Release forks in reverse order of acquisition
    if (philo->left_fork < philo->right_fork)
    {
        pthread_mutex_unlock(&philo->forks[philo->right_fork]);
        pthread_mutex_unlock(&philo->forks[philo->left_fork]);
    }
    else
    {
        pthread_mutex_unlock(&philo->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->forks[philo->right_fork]);
    }
}

// Think implementation (already provided but modified for timestamp)
void think(t_philo *philo)
{
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_THINK);
}

// Sleep implementation (modified from provided version)
void sleep_and_think(t_philo *philo)
{
    printf("%llu %d %s", get_time() - philo->start_time, philo->id, PHILO_SLEEP);
    precise_usleep(philo->time_to_sleep);
    think(philo);
}

// Main philosopher routine
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    // Stagger philosopher start times to reduce contention
    if (philo->id % 2)
        precise_usleep(philo->time_to_eat / 2);
    
    while (1)
    {
        pthread_mutex_lock(&philo->mutex);
        if (philo->is_dead || (philo->number_of_eats != -1 && 
            philo->eat_count >= philo->number_of_eats))
        {
            pthread_mutex_unlock(&philo->mutex);
            break;
        }
        pthread_mutex_unlock(&philo->mutex);
        
        take_fork(philo);
        eat(philo);
        sleep_and_think(philo);
    }
    return (NULL);
}

// Check if philosopher died
int check_is_death(t_philo *philo)
{
    unsigned long long current_time;
    
    pthread_mutex_lock(&philo->mutex);
    current_time = get_time() - philo->start_time;
    if (!philo->is_eating && 
        (current_time - philo->last_eat) > (unsigned long long)philo->time_to_die)
    {
        printf("%llu %d %s", current_time, philo->id, PHILO_DEAD);
        philo->is_dead = 1;
        pthread_mutex_unlock(&philo->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->mutex);
    return (0);
}

// Monitor routine to check for death or completion
void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    int i;
    int all_ate;
    
    while (1)
    {
        i = -1;
        all_ate = 1;
        while (++i < philos->number_of_philosophers)
        {
            if (check_is_death(&philos[i]))
                return (NULL);
                
            pthread_mutex_lock(&philos[i].mutex);
            if (philos[i].number_of_eats != -1 && 
                philos[i].eat_count < philos[i].number_of_eats)
                all_ate = 0;
            pthread_mutex_unlock(&philos[i].mutex);
        }
        
        if (all_ate && philos->number_of_eats != -1)
        {
            pthread_mutex_lock(&philos[0].mutex);
            philos[0].is_dead = 1;
            pthread_mutex_unlock(&philos[0].mutex);
            return (NULL);
        }
        precise_usleep(1000); // Small sleep to prevent busy waiting
    }
    return (NULL);
}