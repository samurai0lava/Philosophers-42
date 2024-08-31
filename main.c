#include "philo.h"

static void init_struct(t_philo *philo)
{
    philo->id = 0;
    philo->left_fork = 0;
    philo->right_fork = 0;
    philo->eat_count = 0;
    philo->last_eat = 0;
    philo->is_eating = 0;
    philo->is_sleeping = 0;
    philo->is_thinking = 0;
    philo->is_dead = 0;
    philo->forks = NULL;
    philo->print = NULL;
    philo->eat = NULL;
}

int main(int ac, char **av)
{
    t_philo philo;

    init_struct(&philo);

    return (0);
}