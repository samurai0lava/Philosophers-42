#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

// make a good version of usleep
// setup a function for time
int usleep_pr(__U64_TYPE usec)
{
	//PRECISE USLEEP
	//ALGO
	//T-T
	

}















__U64_TYPE	get_time(void)
{
	struct timeval	tv;
	__U64_TYPE		start;
	__U64_TYPE		end;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	start = tv.tv_usec;
	printf("tv_usec_start: %ld\n", start);
	usleep(10000);
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	end = tv.tv_usec;
	printf("tv_usec_end: %ld\n", end);
	return (end - start);
}

int	main(void)
{
	printf("tv_usec: %ld\n", get_time());
	return (0);
}