#include "philo.h"

void *monitor(void *arg)
{
    t_philo *philos = (t_philo *)arg;

    while (1)
    {
        pthread_mutex_lock(philos[0].shared_data.dead);
        if (philos[0].shared_data.is_dead == 1)
        {
            pthread_mutex_unlock(philos[0].shared_data.dead);
            return (NULL);
        }
        pthread_mutex_unlock(philos[0].shared_data.dead);

        if (check_if_all_ate(philos) == 1 || check_is_dead(philos) == 1)
            return (NULL);
    }
    return (arg);
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
        pthread_mutex_lock(philos[i].shared_data.dead);
        if (current_time - philos[i].last_meal_time > philos[i].philo_data.time_to_die && philos[i].shared_data.is_eating == 0)
        {
            printf(RED "%lld %d died\n" RESET, get_time() - philos->shared_data.start_time, philos[i].id);
            philos[0].shared_data.is_dead = 1;
            pthread_mutex_unlock(philos[i].shared_data.dead);
            pthread_mutex_unlock(&philos[i].shared_data.state_mutex);
            return (1);
        }
        pthread_mutex_unlock(philos[i].shared_data.dead);
        pthread_mutex_unlock(&philos[i].shared_data.state_mutex);
        i++;
    }
    return (0);
}

int check_if_all_ate(t_philo *philos)
{
    int i;
    int finished_eating;

    pthread_mutex_lock(&philos[0].shared_data.state_mutex);
    i = 0;
    finished_eating = 0;
    if (philos[0].philo_data.number_of_eats == -1)
    {
        pthread_mutex_unlock(&philos[0].shared_data.state_mutex);
        return (0);
    }
    while (i < philos[0].philo_data.numb_of_philos)
    {
        pthread_mutex_lock(&philos[i].shared_data.eats);
        if (philos[i].eat_count >= philos[i].philo_data.number_of_eats)
            finished_eating++;
        pthread_mutex_unlock(&philos[i].shared_data.eats);
        i++;
    }
    pthread_mutex_unlock(&philos[0].shared_data.state_mutex);

    if (finished_eating == philos[0].philo_data.numb_of_philos)
    {
        pthread_mutex_lock(philos[0].shared_data.dead);
        philos[0].shared_data.is_dead = 1;
        pthread_mutex_unlock(philos[0].shared_data.dead);
        return (1);
    }
    return (0);
}
