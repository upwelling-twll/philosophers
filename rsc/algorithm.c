#include "../phylosopher.h"

void	*print_action(int n, int action)
{
	printf("Phylosopher #%i is", n);
	if (action == 1)
		write(1, "eating\n", 8);
	if (action == 2)
		write(1, "sleeping\n", 10);
	if (action == 3)
		write(1, "dead\n", 6);
	return (NULL);
}

void	*philo(t_param *data)
{
	while (1)
	{
		if (data->plist->index %2 == 0)
			usleep(2500);
		if (data->must_die)
			return ;
		lock(min_fork);
		lock(mutex_pintf);
		print_action(data->n, took_left_fork);
		unlock(mutex_pintf);
		if (data->must_die)
			return ;
		lock(max_fork);
		lock(mutex_pintf);
		print_action(data->n, took_right_fork);
		unlock(mutex_pintf);
		if (data->must_die)
			return ;
		lock(mutex_pintf);
		print_action(data->n, eating);
		data->plist->lst_eatung_time = gettimeofaday(*, 0) - data->prog_start * 1000;
		unlock(mutex_pintf);
		usleep(data->time_to_eat);
		unlock(min_fork);
		unlock_(max_fork);
		if (data->must_die)
			return ;
		lock(mutex_pintf);
		print_action(data->n, sleaping);
		unlock(mutex_pintf);
		usleep(data->time_to_sleep);
	}
}

int	is_dead(t_param *data, t_phlst *philo)
{
	if (gettimeofday(NULL, NULL) * 100 - philo->lst_eating_time > data->time_to_sleep)
	{

		print_action
		return (1);
	}
	return (0);
}

int	phylosophers_act(t_param *data) //optional - turns_to_eat
{
	int		n;
	t_phlst	*plist;

	n = 0;
	init_phylo_list(plist, data->n);
	while (n < data->n)
	{
		pthread_create(some, some, philo, data);
		n++;
	}
	while (1)
	{
		n = data->n;
		while (n)
		{
			if (is_dead(data, data->plist))
			{
				data->must_die = 1;
				join_all_threads(plist);
				destroy_all_mutex(mutexes);
				return(exit_phylo(data, 0));
			}
			data->plist = plist->next;
			n++;
		}
		for (philo in philosophers)
	}
	return (0);
}

/*


*/