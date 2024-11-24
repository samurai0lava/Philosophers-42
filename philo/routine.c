#include "philo.h"

void eat(t_philo *philo)
{
    int first_fork;
    int second_fork;

	first_fork = philo->shared_data.left_fork;
	second_fork = philo->shared_data.right_fork;
    if (philo->id % 2 == 0)
	{
        first_fork = philo->shared_data.right_fork;
        second_fork = philo->shared_data.left_fork;
    }
    pthread_mutex_lock(&philo->shared_data.forks[first_fork]);
    printf(GREEN "%llu %d %s" RESET, get_time() - philo->shared_data.start_time, philo->id, PHILO_FORK);
    pthread_mutex_lock(&philo->shared_data.forks[second_fork]);
    printf(GREEN "%llu %d %s" RESET, get_time() - philo->shared_data.start_time, philo->id, PHILO_FORK);
    pthread_mutex_lock(&philo->shared_data.state_mutex);
    philo->last_meal_time = get_time();
    philo->eat_count++;
    printf(ORANGE "%llu %d %s" RESET, get_time() - philo->shared_data.start_time, philo->id, PHILO_EAT);
    pthread_mutex_unlock(&philo->shared_data.state_mutex);
    precise_usleep(philo->philo_data.time_to_eat);
    pthread_mutex_unlock(&philo->shared_data.forks[second_fork]);
    pthread_mutex_unlock(&philo->shared_data.forks[first_fork]);
}

void sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_data.print);
	printf(YELLOW "%lld %d is sleeping\n" RESET, get_time() - philo->shared_data.start_time, philo->id);
	pthread_mutex_unlock(philo->shared_data.print);
	precise_usleep(philo->philo_data.time_to_sleep);
	pthread_mutex_lock(philo->shared_data.print);
	printf(ORANGE "%lld %d is thinking\n" RESET, get_time() - philo->shared_data.start_time, philo->id);
	pthread_mutex_unlock(philo->shared_data.print);
}

int dead_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_data.dead);
	if (philo->shared_data.is_dead == 1)
	{
		pthread_mutex_unlock(philo->shared_data.dead);
		return (1);
	}
	pthread_mutex_unlock(philo->shared_data.dead);
	return (0);
}

void *routine(void *arg)
{
	t_philo     *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(10);
	while (dead_philo(philo) == 0)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
