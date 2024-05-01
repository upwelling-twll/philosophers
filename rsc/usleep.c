#include "../phylosopher.h"

long long	timestamp(void)
{
	struct timeval	timestrc;

	gettimeofday(&timestrc, NULL);
	return((timestrc.tv_sec * 1000) + (timestrc.tv_usec / 1000)* 1000);
}

long long	time_diff(long long past, long long present)
{
	// printf("DIFF=%lli\n", present - past);
	return(present - past);
}

int	prog_end(t_param *data)
{
	pthread_mutex_lock(&(data->param_mutex));
	if (data->prog_must_die == 1)
	{
		pthread_mutex_unlock(&(data->param_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->param_mutex));
	return (0);
}

int		my_usleep(long long time, t_param *data)
{
	long long start;

	start = timestamp();
	while (!(prog_end(data)))
	{
		// printf("goal: %lli\n", time);
		if (time_diff(start, timestamp()) >= time)
			return (0);
		usleep(50);
	}
	return (1);
}

// void	my_usleep(int	period)
// {
// 	struct timeval	start;
// 	struct timeval	curr;
// 	size_t			time_passed;

// 	gettimeofday(&start, NULL);
// 	gettimeofday(&curr, NULL);
// 	while((curr.tv_sec * 1000000 + curr.tv_usec) - period < (start.tv_sec * 1000000 + start.tv_usec))
// 	{
// 		usleep(100);
// 		gettimeofday(&curr, NULL);
// 	}
// }
