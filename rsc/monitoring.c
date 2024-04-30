#include "../phylosopher.h"

int	is_dead(t_param *data, t_phlst *philo)
{
	size_t	time_after_eating;
	struct timeval	cur;

	if (philo->turns == 0)
		return (0);
	gettimeofday(&cur, NULL);	
	time_after_eating = (cur.tv_sec - philo->lst_eating_time.tv_sec) 
		* 1000000 + (cur.tv_usec - philo->lst_eating_time.tv_usec);
	pthread_mutex_lock(&(philo->philo_mutex));	
	if (philo->is_eating == 1)
	{
		pthread_mutex_unlock(&(philo->philo_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philo->philo_mutex));
	if (time_after_eating > data->time_to_die )
	{
		pthread_mutex_lock(&(data->param_mutex));
		data->prog_must_die = 1;
		pthread_mutex_unlock(&(data->param_mutex));
		pthread_mutex_lock(&(data->mutex_printf));	
		print_action(philo->index, 6,  *(philo->param));
		pthread_mutex_unlock(&(data->mutex_printf));
		return (1);
	}
	return (0);
}

int	everyone_ate_turns(int turns_to_eat, t_phlst **philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_lock(&(philos[i]->philo_mutex));
		if (philos[i]->turns != turns_to_eat)
		{
			pthread_mutex_unlock(&(philos[i]->philo_mutex));
			return (0);
		}
		pthread_mutex_unlock(&(philos[i]->philo_mutex));
		i++;
	}
	return (1);
}

int	monitore_while_turns(t_param *data)
{
	int	i;

	i = 0;
	while (!(everyone_ate_turns(data->turns_to_eat, data->plist, data->n)))
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

int	monitore_endlessly(t_param *data)
{
	int	i;

	i = 0;
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
