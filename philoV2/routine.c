#include "philo.h"

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->shared_data.forks[philo->shared_data.left_fork]);
    printf(GREEN "%llu %d %s" RESET, get_time() - philo->shared_data.start_time, philo->id, PHILO_FORK);
    pthread_mutex_lock(&philo->shared_data.forks[philo->shared_data.right_fork]);
    printf(GREEN "%llu %d %s" RESET, get_time() - philo->shared_data.start_time, philo->id, PHILO_FORK);
    pthread_mutex_lock(&philo->shared_data.state_mutex);
    philo->shared_data.is_eating = 1;
    philo->last_meal_time = get_time() - philo->shared_data.start_time;
    philo->eat_count++;
    printf(ORANGE "%llu %d %s" RESET, get_time() - philo->shared_data.start_time, philo->id, PHILO_EAT);
    pthread_mutex_unlock(&philo->shared_data.state_mutex);
    precise_usleep(philo->philo_data.time_to_eat);
    pthread_mutex_lock(&philo->shared_data.state_mutex);
    philo->shared_data.is_eating = 0;
    pthread_mutex_unlock(&philo->shared_data.state_mutex);
    pthread_mutex_unlock(&philo->shared_data.forks[philo->shared_data.right_fork]);
    pthread_mutex_unlock(&philo->shared_data.forks[philo->shared_data.left_fork]);
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

int check_is_dead(t_philo *philos)
{
    int i;
    long long current_time;

    i = 0;
    while (i < philos[0].philo_data.numb_of_philos)
    {
        current_time = get_time();
        pthread_mutex_lock(&philos[i].shared_data.state_mutex);
        if (current_time - philos[i].last_meal_time > philos[i].philo_data.time_to_die && philos[i].shared_data.is_eating == 0)
        {
            printf(RED "%lld %d died\n" RESET, get_time() - philos->shared_data.start_time, philos[i].id);
			pthread_mutex_lock(philos[i].shared_data.dead);
            philos[0].shared_data.is_dead = 1;
			pthread_mutex_unlock(philos[i].shared_data.dead);
            pthread_mutex_unlock(&philos[i].shared_data.state_mutex);
            return (1);
        }
        pthread_mutex_unlock(&philos[i].shared_data.state_mutex);
        i++;
    }
    return (0);
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
		precise_usleep(500);
	while (dead_philo(philo) == 0)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

void *monitor(void *arg)
{
	t_philo *philos = (t_philo *)arg;

	while (1)
	{
		if (check_if_all_ate(philos) == 1 || check_is_dead(philos) == 1)
			break;
		precise_usleep(10);
	}
	return (arg);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].philo_data.number_of_eats == -1)
		return (0);
	while (i < philos[0].philo_data.numb_of_philos)
	{
		pthread_mutex_lock(&philos[i].shared_data.eats);
		if (philos[i].eat_count >= philos[i].philo_data.number_of_eats)
			finished_eating++;
		pthread_mutex_unlock(&philos[i].shared_data.eats);
		i++;
	}
	if (finished_eating == philos[0].philo_data.numb_of_philos)
	{
		pthread_mutex_lock(philos[0].shared_data.dead);
		philos[0].shared_data.is_dead = 1;
		pthread_mutex_unlock(philos[0].shared_data.dead);
		return (1);
	}
	return (0);
}