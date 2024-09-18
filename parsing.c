#include "philo.h"

int parse_input(int ac, char **av, t_philo *philo)
{
	//test is numeric 
	//test if the minumm number of argumanets required
	//test max int i guess (to look it up)
	//convert the input into integer
	//check overflow
	//asign it to the struct (i need an other function)
	if(ac == 4 || ac == 5)
	{

	}
	else
	{
		printf(RED "number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n" RESET);
		return (1);
	}
}