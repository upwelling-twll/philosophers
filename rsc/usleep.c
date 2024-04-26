#include "../phylosopher.h"

void	my_usleep(int	period)
{
	struct timeval	start;
	struct timeval	curr;
	size_t			time_passed;

	gettimeofday(&start, NULL);
	gettimeofday(&curr, NULL);
	while((curr.tv_sec - start.tv_sec) + (curr.tv_usec - start.tv_usec) < period)
	{
		usleep(100);
		gettimeofday(&curr, NULL);
	}
}