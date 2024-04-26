#include "../phylosopher.h"

void	*print_action(int n, int action)
{
	printf("Phylosopher #%i ", n);
	if (action == 1)
		printf("is eating\n");
	if (action == 2)
		printf("is sleeping\n");
	if (action == 3)
		printf("is dead\n");
	if (action == 4)
		printf("took left fork\n");
	if (action == 5)
		printf("took right fork\n");
	if (action == 6)
		printf("is sratving\n");
	if (action == 7)
		printf("is thinking\n");
	if (action == 9)
		printf("done eating\n");
	return (NULL);
}

pthread_mutex_t	*min_fork(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork < one_philo->right_fork->fork)
		return (&one_philo->left_fork->fork_mutex);
	else
		return (&one_philo->right_fork->fork_mutex);
}

pthread_mutex_t	*max_fork(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork > one_philo->right_fork->fork)
		return (&one_philo->left_fork->fork_mutex);
	else
		return (&one_philo->right_fork->fork_mutex);
}

int	someone_is_dead(t_param *shared_data, pthread_mutex_t sd_mutex)
{
	pthread_mutex_lock(&sd_mutex);
	if (shared_data->prog_must_die)
	{
		pthread_mutex_unlock(&sd_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sd_mutex);
	return (0);
}

void	*philo(void *one_philo)
{
	int i;
	struct s_list_phylo *plist;
	t_param	*shared_data;
	struct timeval	cur_time;
	pthread_mutex_t	sd_mutex;

	i = 0;
	plist = (struct s_list_phylo *)(one_philo);
	shared_data = *(plist->param);
	sd_mutex = shared_data->param_mutex;
	while (1)
	{
		if (plist->index%2 == 0)
			my_usleep(2500);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		pthread_mutex_lock(min_fork(plist));
		pthread_mutex_lock(&shared_data->mutex_printf);
			print_action((plist)->index, 4); //took_left_fork
		pthread_mutex_unlock(&shared_data->mutex_printf);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);	
		pthread_mutex_lock(max_fork((plist)));
		pthread_mutex_lock(&shared_data->mutex_printf);
			print_action(plist->index, 5); //took_right_fork
		pthread_mutex_unlock(&shared_data->mutex_printf);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		pthread_mutex_lock(&shared_data->mutex_printf);

		print_action(plist->index, 1); //eating
		pthread_mutex_unlock(&shared_data->mutex_printf);
		my_usleep(shared_data->time_to_eat);
		gettimeofday(&cur_time, NULL);
		plist->lst_eating_time = cur_time;
		plist->turns ++;
		
		int	has_eaten;
		has_eaten = (cur_time.tv_sec - plist->lst_eating_time.tv_sec)*100000 + (cur_time.tv_usec - plist->lst_eating_time.tv_usec);
		pthread_mutex_lock(&shared_data->mutex_printf);
			printf("has eaten period:%i, turns_time=%i\n", has_eaten, plist->turns); //debug
		pthread_mutex_unlock(&shared_data->mutex_printf);

		pthread_mutex_unlock(min_fork(plist));
		pthread_mutex_unlock(max_fork(plist));

		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		pthread_mutex_lock(&shared_data->mutex_printf);
			print_action(plist->index, 2); //sleeping
		pthread_mutex_unlock(&shared_data->mutex_printf);
		my_usleep(shared_data->time_to_sleep);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		i++;
	}
}

void	join_all_threads(t_param *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(data->plist[i]->thread, NULL);
		i++;
	}
}

int	phylosophers_act(t_param *data, t_fork **forks) //optional - turns_to_eat
{
	int		n;
	int		i;
	int		turns;
	t_phlst	*plist[200];
	t_phlst	*head;
	struct timeval	start;

	n = 0;
	i = 0;
	printf("hi\n");
	init_plist_and_forks(plist, data->n, forks, data);
	data->plist = plist;
	printf("hello\n");
	print_data_list(data, plist); //dbg
	pthread_mutex_init(&data->mutex_printf, NULL);
	pthread_mutex_init(&data->param_mutex, NULL);
	data->prog_must_die = 0;
	gettimeofday(&start, NULL);
	data->prog_start = start;
	while (n < data->n)
	{
		data->plist[i]->param = &data;
		data->plist[i]->lst_eating_time = data->prog_start = start;
		pthread_create(&data->plist[i]->thread, NULL, philo, (void *)(data->plist[i]));
		n++;
		i++;
	}
	if (data->turns_to_eat == 0)
	{
		if (monitore_endlessly(data))
			return (1);
	}
	else
	{
		if (monitore_while_turns(data))
			return (1);
	}
	join_all_threads(data, data->n);
	//destroy_all_mutex(data, forks);
	return (0);
}

/*


*/