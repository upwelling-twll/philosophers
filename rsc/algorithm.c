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
			if (someone_is_dead(shared_data, sd_mutex))
				return (NULL);
			pthread_mutex_lock(&shared_data->mutex_printf);
			print_action(plist->index, 7, shared_data); //thinking
			pthread_mutex_unlock(&shared_data->mutex_printf);
			usleep(50);
		}
		if (plist->index%2 == 0)
			usleep(2500);
		while (min_fork_last_user(plist) == plist->index || max_fork_last_user(plist) == plist->index)
			usleep(50);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		if (shared_data->n %2 != 0)
			pthread_mutex_lock(min_fork(plist));
		else
			pthread_mutex_lock(max_fork(plist));
		pthread_mutex_lock(&shared_data->mutex_printf);
			print_action((plist)->index, 4,  shared_data); //took_left_fork
		pthread_mutex_unlock(&shared_data->mutex_printf);
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		if (shared_data->n % 2 != 0)
			pthread_mutex_lock(max_fork((plist)));
		else
			pthread_mutex_lock(min_fork((plist)));
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
		pthread_mutex_lock(&(plist->philo_mutex));
		plist->lst_eating_time = cur_time;
		pthread_mutex_unlock(&(plist->philo_mutex));
		pthread_mutex_lock(&(plist->philo_mutex));
		plist->turns ++;
		pthread_mutex_unlock(&(plist->philo_mutex));
		usleep(shared_data->time_to_eat);
		// my_usleep(shared_data->time_to_eat, shared_data);
		
		pthread_mutex_lock(&(plist->philo_mutex));	
		plist->is_eating = 0;
		pthread_mutex_unlock(&(plist->philo_mutex));
		plist->left_fork->last_user = plist->index;
		plist->right_fork->last_user = plist->index;
		pthread_mutex_unlock(min_fork(plist));
		pthread_mutex_unlock(max_fork(plist));
		if (someone_is_dead(shared_data, sd_mutex))
			return (NULL);
		pthread_mutex_lock(&shared_data->mutex_printf);
			print_action(plist->index, 2,  shared_data); //sleeping
		pthread_mutex_unlock(&shared_data->mutex_printf);
		usleep(shared_data->time_to_sleep);
		// my_usleep(shared_data->time_to_sleep, shared_data);
		// if (someone_is_dead(shared_data, sd_mutex))
		// 	return (NULL);
		i++;
		l = l + k;
	}
	return (one_philo);
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
	t_phlst	*plist[200];
	struct timeval	start;

	n = 0;
	i = 0;
	init_plist_and_forks(plist, data->n, forks);
	data->plist = plist;
	data->forks = forks;
	pthread_mutex_init(&data->mutex_printf, NULL);
	pthread_mutex_init(&data->param_mutex, NULL);
	data->prog_must_die = 0;
	gettimeofday(&start, NULL);
	data->prog_start = start;
	while (n < data->n)
	{
		data->plist[i]->param = &data;
		data->plist[i]->lst_eating_time = data->prog_start = start;
		pthread_create(&data->plist[i]->thread, NULL, philo_test, (void *)(data->plist[i]));
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
	destroy_all_mutex(data, forks);
	return (0);
}

/*


*/