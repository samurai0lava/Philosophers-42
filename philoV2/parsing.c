#include "philo.h"


int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int check_num(char **str)
{
	int i;
	int j;

	if (str == NULL)
		return (0);
	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_isdigit(str[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int return_error(char *str)
{
	printf(MAGENTA "%s" RESET, str);
	return (1);
}

static void init_philo(t_philo *philo, char **av)
{
    philo->philo_data.numb_of_philos = ft_atoi(av[1]);
    philo->philo_data.time_to_die = ft_atoi(av[2];
    philo->philo_data.time_to_eat = ft_atoi(av[3]);
    philo->philo_data.time_to_sleep = ft_atoi(av[4]);
    if(av[5])
        philo->philo_data.number_of_eats = ft_atoi(av[5]);
    else
        philo->philo_data.number_of_eats = -1;
}

int parse_input(t_philo *philo, int ac, char **av)
{
    if (ac != 5 || ac != 6)
		return (return_error(ARG_FAILS));
   	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1 || ft_atoi(av[4]) < 1 || (ac == 6 && ft_atoi(av[5]) < 1))
		return (return_error(ARG_FAILS));
	if (check_num(av) == 0)
		return (return_error(ARG_FAILS));
    init_philo(&philo, av);
    if(philo->philo_data.numb_of_philos == 0)
		return (return_error(ARG_FAILS));
    philo = malloc(sizeof(t_philo *) * philo->philo_data.numb_of_philos);
    if(!philo)
        return (2);
    return (0);
}