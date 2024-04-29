#include "../phylosopher.h"

long long	timestamp(void)
{
	struct timeval	timestrc;
	long long	time;

	gettimeofday(&timestrc, NULL);
	time = timestrc.tv_sec * 1000 + timestrc.tv_usec / 1000;
	return (time);
}

long long	time_diff(long long past, long long present)
{
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

void		my_usleep(long long time, t_param *data)
{
	long long start;

	start = timestamp();
	while (!(prog_end(data)))
	{
		if (time_diff(start, timestamp()) >= time)
			break ;
		usleep(50);
	}
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
