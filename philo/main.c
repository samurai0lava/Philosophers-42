#include "philo.h"

int create_thread_monitor(t_philo *philos)
{
	int check;

	check = pthread_create(&philos[0].shared_data.monitor_thread, NULL, &monitor, philos);
	if (check != 0)
		return (1);
	return (0);
}

int creath_thread(t_philo *philos)
{
	int	i;
	int check;

	i = 0;
	while(philos[0].philo_data.numb_of_philos > i)
	{
		check = pthread_create(&philos[i].shared_data.philos[i], NULL, &routine, &philos[i]);
		if (check != 0)
			return (1);
		pthread_detach(philos[i].shared_data.philos[i]);
		i++;
	}
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
		pthread_mutex_init(&philos[0].shared_data.state_mutex, NULL) ||
		pthread_mutex_init(&philos[0].shared_data.eats, NULL))
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
		philos[i].shared_data.left_fork = i;
		philos[i].shared_data.right_fork = (i + 1) % philos[0].philo_data.numb_of_philos;
		philos[i].shared_data.start_time = get_time();
		philos[i].shared_data.is_eating = 0;
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
	pthread_mutex_destroy(&philos[0].shared_data.state_mutex);
	pthread_mutex_destroy(&philos[0].shared_data.eats);
	free(philos[0].shared_data.forks);
	free(philos[0].shared_data.print);
	free(philos[0].shared_data.dead);
	free(philos[0].shared_data.philos);
	if(philos != NULL)
		free(philos);
	philos = NULL;
}

void handle_one_philo(t_philo *philos)
{
	precise_usleep(philos[0].philo_data.time_to_die);
	pthread_mutex_lock(philos[0].shared_data.print);
	printf(RED "%lld %d died\n" RESET, get_time() - philos[0].shared_data.start_time, philos[0].id);
	pthread_mutex_unlock(philos[0].shared_data.print);
	philos[0].shared_data.is_dead = 1;
}

int start_simulation(t_philo *philos)
{
	long long   start_time; 
	int         i;

	i = 0;
	start_time = get_time();
	philos[0].last_meal_time = start_time;
	if (create_thread_monitor(philos) != 0)
		return (1);
	if (creath_thread(philos) != 0)
		return (1);
	pthread_join(philos[0].shared_data.monitor_thread, NULL);
	while(i <= philos[0].philo_data.numb_of_philos)
	{
	    if (pthread_join(philos[0].shared_data.philos[i], NULL) != 0)
	        return (1);
	    i++;
	}
	return (0);
}

int main(int ac , char **av)
{
	t_philo *philos;
	int     numbofphilos;

	if (ac != 5 && ac != 6)
		return (return_error(ARG_FAILS));
	numbofphilos = parse_num_of_philos(av[1]);
	if (numbofphilos == -1)
		return (return_error(ARG_FAILS));
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philos)
		return (1);
	if (parse_input(philos, ac, av) != 0)
		return (free(philos),1);
	if (init_mutexes(philos) != 0)
		return (cleanup(philos),1);
	init_philosophers(philos);
	if(philos[0].philo_data.numb_of_philos == 1)
		return (handle_one_philo(philos),cleanup(philos),0);
	if (start_simulation(philos) != 0)
		return (cleanup(philos),1);
	cleanup(philos);
	return (0);
}
