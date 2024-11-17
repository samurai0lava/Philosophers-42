#include "philo.h"

int creath_thread(t_philo *philo)
{
    int i;
    int check;

    i = 0;
    while(philo->philo_data.numb_of_philos > i)
    {
        check = pthread_create(&philo->shared_data.philos[i], NULL, &routine, &philo->philo_data);
        if (check != 0)
            return (1);
        i++;
    }
    return (0);
}

int create_thread_monitor(t_philo *philo)
{
    int check;

    check = pthread_create(&philo->shared_data.philos[philo->philo_data.numb_of_philos], NULL, &monitor, &philo->philo_data);
    if (check != 0)
        return (1);
    return (0);
}

int main(int ac , char **av)
{
    t_philo philo;

    if(init_philo(&philo, ac, av) != 0)
        return(1);
    
    
    


}