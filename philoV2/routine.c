#include "philo.h"

void take_fork(t_philo *philo)
{

    pthread_mutex_lock(&philo->shared_data.forks[philo->shared_data.left_fork]);
    pthread_mutex_lock(philo->shared_data.print);
    printf(GREEN "%lld %d has taken a fork\n" RESET, get_time() - philo->shared_data.start_time, philo->id);
    pthread_mutex_unlock(philo->shared_data.print);
    
    pthread_mutex_lock(&philo->shared_data.forks[philo->shared_data.right_fork]);
    pthread_mutex_lock(philo->shared_data.print);
    printf(GREEN "%lld %d has taken a fork\n" RESET, get_time() - philo->shared_data.start_time, philo->id);
    pthread_mutex_unlock(philo->shared_data.print);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_data.print);
    printf(BLUE "%lld %d is eating\n" RESET, get_time() - philo->shared_data.start_time, philo->id);
    pthread_mutex_unlock(philo->shared_data.print);
    pthread_mutex_lock(&philo->shared_data.state_mutex);
    philo->last_meal_time = get_time();
    philo->eat_count++;
    pthread_mutex_unlock(&philo->shared_data.state_mutex);
    precise_usleep(philo->philo_data.time_to_eat * 1000);
    pthread_mutex_unlock(&philo->shared_data.forks[philo->shared_data.left_fork]);
    pthread_mutex_unlock(&philo->shared_data.forks[philo->shared_data.right_fork]);
}

void sleep_and_think(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_data.print);
    printf(YELLOW "%lld %d is sleeping\n" RESET, get_time() - philo->shared_data.start_time, philo->id);
    pthread_mutex_unlock(philo->shared_data.print);
    precise_usleep(philo->philo_data.time_to_sleep * 1000);
    pthread_mutex_lock(philo->shared_data.print);
    printf(ORANGE "%lld %d is thinking\n" RESET, get_time() - philo->shared_data.start_time, philo->id);
    pthread_mutex_unlock(philo->shared_data.print);
}

void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        precise_usleep(1000);
    while (1)
    {
        pthread_mutex_lock(&philo->shared_data.state_mutex);
        if (philo->shared_data.is_dead)
        {
            pthread_mutex_unlock(&philo->shared_data.state_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->shared_data.state_mutex);
        take_fork(philo);
        eat(philo);
        if (philo->eat_count == philo->philo_data.number_of_eats)
            break;
        sleep_and_think(philo);
    }
    return (NULL);
}

void *monitor(void *arg)
{
    t_philo *philo;
    long long current_time;
    
    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philo->shared_data.state_mutex);
        if (philo->shared_data.is_dead)
        {
            pthread_mutex_unlock(&philo->shared_data.state_mutex);
            break;
        }
        current_time = get_time();
        if (current_time - philo->last_meal_time > philo->philo_data.time_to_die)
        {
            pthread_mutex_lock(philo->shared_data.dead);
            pthread_mutex_lock(philo->shared_data.print);
            philo->shared_data.is_dead = 1;
            printf(RED "%lld %d died\n" RESET, current_time - philo->shared_data.start_time, philo->id);
            pthread_mutex_unlock(philo->shared_data.print);
            pthread_mutex_unlock(philo->shared_data.dead);
            pthread_mutex_unlock(&philo->shared_data.state_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->shared_data.state_mutex);
        precise_usleep(1000);
    }
    return (NULL);
}