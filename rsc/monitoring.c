#include "../phylosopher.h"

int	is_dead(t_param *data, t_phlst *philo)
{
	size_t	time_after_eating;
	struct timeval	cur;

	if (philo->turns == 0)
		return (0);
	gettimeofday(&cur, NULL);
	time_after_eating = (cur.tv_sec - philo->lst_eating_time.tv_sec) + (cur.tv_usec - philo->lst_eating_time.tv_usec);
	pthread_mutex_lock(&(data->mutex_printf));	
	//printf("lst_eating_time | time_to_die\n        %li       |     %i     \n", time_after_eating, data->time_to_die);
	pthread_mutex_unlock(&(data->mutex_printf));
	if (time_after_eating > data->time_to_die)
	{
		pthread_mutex_lock(&(data->mutex_printf));	
		print_action(philo->index, 6);
		printf("current_mm_time: sec:%li usec:%li\n", cur.tv_sec, cur.tv_usec);
		printf("lst_eating_time: sec:%li usec:%li\n", philo->lst_eating_time.tv_sec, philo->lst_eating_time.tv_usec);
		printf("time_after_eating: %zu \n", time_after_eating);
		pthread_mutex_unlock(&(data->mutex_printf));
		return (1);
	}
	return (0);
}

int	monitore_while_turns(t_param *data)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	printf("monitoring_turns\n");
	while (t < data->turns_to_eat)
	{
		while (i < data->n)
		{
			if (is_dead(data, data->plist[i]))
			{
				pthread_mutex_lock(&(data->param_mutex));
				data->prog_must_die = 1;
				pthread_mutex_unlock(&(data->param_mutex));
				join_all_threads(data, data->n);
				//destroy_all_mutex(data, forks);
				return (1);
				//return(exit_phylo(data, 0));
			}
			i++;
		}
		t++;
	}
	return (0);
}

int	monitore_endlessly(t_param *data)
{
	int	i;

	i = 0;
	printf("monitoring_endlessly\n");
	while (1)
	{
		i = 0;
		while (i < data->n)
		{
			if (is_dead(data, data->plist[i]))
			{
				pthread_mutex_lock(&(data->param_mutex));
				data->prog_must_die = 1;
				pthread_mutex_unlock(&(data->param_mutex));
				join_all_threads(data, data->n);
				//destroy_all_mutex(data, forks);
				return (1);
				//return(exit_phylo(data, 0));
			}
			i++;
		}
	}
	return (0);
}