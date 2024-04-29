#include "../phylosopher.h"

void	*print_action(int n, int action, t_param *data)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	printf("%li ", ((time_now.tv_sec * 1000000 + time_now.tv_usec) - (data->prog_start.tv_sec * 1000000 + data->prog_start.tv_usec)) / 1000);
	printf("%i ", n);
	if (action == 1)
		printf("is eating\n");
	if (action == 2)
		printf("is sleeping\n");
	if (action == 3)
		printf("is dead\n");
	if (action == 4 || action == 5)
		printf("has taken a fork\n");
	// if (action == 4 && n != data->n)
	// 	printf("took left fork\n");
	// if (action == 4 && n == data->n)
	// 	printf("took right fork\n");
	// if (action == 5 && n != data->n)
	// 	printf("took right fork\n");
	// if (action == 5 && n == data->n)
	// 	printf("took left fork\n");
	if (action == 6)
		printf("died\n");
	// if (action == 6)
	// 	printf("is starving\n");
	if (action == 7)
		printf("is thinking\n");
	if (action == 9)
		printf("done eating\n");
	if (action == 10)
		printf("is no more using a min fork\n");
	if (action == 11)
		printf("is no more using max fork\n");
	if (action == 12)
		printf("done thinking\n");
	return (NULL);
}

int	min_fork_last_user(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork < one_philo->right_fork->fork)
		return (one_philo->left_fork->last_user);
	else
		return (one_philo->right_fork->last_user);
}

int	max_fork_last_user(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork > one_philo->right_fork->fork)
		return (one_philo->left_fork->last_user);
	else
		return (one_philo->right_fork->last_user);
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
	int	l;
	int	k;
	int	turns;
	struct s_list_phylo *plist;
	t_param	*shared_data;
	struct timeval	cur_time;
	pthread_mutex_t	sd_mutex;

	i = 0;
	l = 0;
	plist = (struct s_list_phylo *)(one_philo);
	shared_data = *(plist->param);
	sd_mutex = shared_data->param_mutex;
	if (shared_data->turns_to_eat > 0)
	{
		l = 0;
		k = 1;
		turns = shared_data->turns_to_eat;
	}
	else
	{
		k = 0;
		turns = 1;
	}
	while (l < turns)
	{
		if (plist->turns != 0)
		{
			// struct timeval thinking_time;
			// gettimeofday(&thinking_time, NULL);
			// plist->thinking_time = thinking_time;
			if (someone_is_dead(shared_data, sd_mutex))
				return (NULL);
			pthread_mutex_lock(&shared_data->mutex_printf);
			print_action(plist->index, 7, shared_data); //thinking
			//printf("thnk_start_time: sec:%zu usec:%zu\n", thinking_time.tv_sec, thinking_time.tv_usec);
			pthread_mutex_unlock(&shared_data->mutex_printf);
			usleep(50);
			// pthread_mutex_lock(&shared_data->mutex_printf);
			// print_action(plist->index, 12); //thinking
			// pthread_mutex_unlock(&shared_data->mutex_printf);
		}
		if (plist->index%2 == 0)
			usleep(2500);
		while (min_fork_last_user(plist) == plist->index || max_fork_last_user(plist) == plist->index)
			usleep(50);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		pthread_mutex_lock(min_fork(plist));
		pthread_mutex_lock(&shared_data->mutex_printf);
			print_action((plist)->index, 4,  shared_data); //took_left_fork
		pthread_mutex_unlock(&shared_data->mutex_printf);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);	
		pthread_mutex_lock(max_fork((plist)));
		pthread_mutex_lock(&shared_data->mutex_printf);
			print_action(plist->index, 5,  shared_data); //took_right_fork
		pthread_mutex_unlock(&shared_data->mutex_printf);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		pthread_mutex_lock(&(plist->philo_mutex));	
		plist->is_eating = 1;
		pthread_mutex_unlock(&(plist->philo_mutex));
		pthread_mutex_lock(&shared_data->mutex_printf);
		print_action(plist->index, 1,  shared_data); //eating
		pthread_mutex_unlock(&shared_data->mutex_printf);
			gettimeofday(&cur_time, NULL);
		plist->lst_eating_time = cur_time;
		plist->turns ++;
		my_usleep(shared_data->time_to_eat, shared_data);
		
		pthread_mutex_lock(&(plist->philo_mutex));	
		plist->is_eating = 0;
		pthread_mutex_unlock(&(plist->philo_mutex));
		// int	has_eaten;
		// has_eaten = (cur_time.tv_sec - plist->lst_eating_time.tv_sec)*100000 + (cur_time.tv_usec - plist->lst_eating_time.tv_usec);
		// pthread_mutex_lock(&shared_data->mutex_printf);
		// 	printf("has eaten period:%i, turns_time=%i\n", has_eaten, plist->turns); //debug
		// pthread_mutex_unlock(&shared_data->mutex_printf);
		plist->left_fork->last_user = plist->index;
		plist->right_fork->last_user = plist->index;
		pthread_mutex_unlock(min_fork(plist));
		// pthread_mutex_lock(&shared_data->mutex_printf);
		// 	print_action(plist->index, 10); //not_usin_min_fork
		// pthread_mutex_unlock(&shared_data->mutex_printf);
		pthread_mutex_unlock(max_fork(plist));
		// pthread_mutex_lock(&shared_data->mutex_printf);
		// 	print_action(plist->index, 11); //not_usin_max_fork
		// pthread_mutex_unlock(&shared_data->mutex_printf);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		pthread_mutex_lock(&shared_data->mutex_printf);
			print_action(plist->index, 2,  shared_data); //sleeping
		pthread_mutex_unlock(&shared_data->mutex_printf);
		my_usleep(shared_data->time_to_sleep, shared_data);
		// if (someone_is_dead(shared_data, sd_mutex))
		// 	return (NULL);
		i++;
		l = l + k;
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
	init_plist_and_forks(plist, data->n, forks, data);
	data->plist = plist;
	//print_data_list(data, plist); //dbg
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