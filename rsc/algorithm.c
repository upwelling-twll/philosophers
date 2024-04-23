#include "../phylosopher.h"

void	*print_action(int n, int action)
{
	printf("Phylosopher #%i is", n);
	if (action == 1)
		write(1, "eating\n", 8);
	if (action == 2)
		write(1, "sleeping\n", 10);
	if (action == 3)
		write(1, "died\n", 6);
	if (action == 4)
		write(1, "has taken a left fork\n", 16);
	if (action == 5)
		write(1, "has taken a right fork\n", 17);
	if (action == 6)
		write(1, "is sratving\n", 13);
	if (action == 7)
		write(1, "thinking\n", 10);
	return (NULL);
}

// void	*philo(t_param *data)
// {
// 	struct timeval	time;

// 	while (1)
// 	{
// 		if (data->plist->index %2 == 0)
// 			usleep(2500);
// 		if (data->must_die)
// 			return (NULL);
// 		lock(min_fork(data));
// 		lock(data->mutex_printf);
// 		print_action(data->n, 4); //took_left_fork
// 		unlock(data->mutex_printf);
// 		if (data->must_die)
// 			return (NULL);
// 		lock(max_fork(data));
// 		lock(data->mutex_printf);
// 		print_action(data->n, 5); //took_right_fork
// 		unlock(data->mutex_printf);
// 		if (data->must_die)
// 			return (NULL);
// 		lock(data->mutex_printf);
// 		print_action(data->n, 1); //eating
// 		data->plist->lst_eating_time.tv_usec = gettimeofaday(&time, NULL) - data->prog_start * 1000;
// 		unlock(data->mutex_printf);
// 		usleep(data->time_to_eat);
// 		unlock(min_fork);
// 		unlock_(max_fork);
// 		if (data->must_die)
// 			return (NULL);
// 		lock(data->mutex_printf);
// 		print_action(data->n, 2); //sleeping
// 		unlock(data->mutex_printf);
// 		usleep(data->time_to_sleep);
// 	}
// }

void	*philo_test(void *plist)
{
	int	i;

	i = 0;
	printf("philo_test\n");
	plist = (struct s_list_phylo *)(plist);
	pthread_mutex_lock(((struct s_list_phylo *)plist)->left_fork->fork_mutex);
	printf("philo #%i took left_fork\n", ((struct s_list_phylo *)plist)->index);
	pthread_mutex_lock(((struct s_list_phylo *)plist)->right_fork->fork_mutex);
	printf("philo #%i took right_fork\n", ((struct s_list_phylo *)plist)->index);
	printf("philo #%i is eating\n", ((struct s_list_phylo *)plist)->index);
	printf("philo #%i is sleeping\n\n",((struct s_list_phylo *)plist)->index);
	pthread_mutex_lock(((struct s_list_phylo *)plist)->left_fork->fork_mutex);
	pthread_mutex_lock(((struct s_list_phylo *)plist)->right_fork->fork_mutex);
}

// int	is_dead(t_param *data, t_phlst *philo)
// {
// 	if ((gettimeofday(NULL, NULL) * 100 - (philo->lst_eating_time.tv_usec)) >= data->time_to_die)
// 	{
// 		print_action(philo->index, 6);
// 		return (1);
// 	}
// 	return (0);
// }

void	join_all_threads(t_phlst *plist, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(plist->thread, NULL);
		i++;
		plist = plist->next;
	}
}

int	phylosophers_act(t_param *data, t_fork **forks) //optional - turns_to_eat
{
	int		n;
	int		i;
	t_phlst	*plist[200];
	t_phlst	*head;

	n = 0;
	i = 0;
	init_plist_and_forks(plist, data->n, forks);
	data->plist = plist;
	print_data_list(data, plist); //dbg
	while (n < data->n)
	{
		pthread_create(data->plist[i]->thread, NULL, philo_test, (void *)(data->plist[i]));
		//pthread_mutex_init(&plist->mutex_for_fork, NULL);
		n++;
		i++;
	}
	// join_all_threads(plist, data->n);

	// data-> = (pthread_mutex_t *)malloc((d_dinner->num_ph) * sizeof(pthread_mutex_t));
	// pthread_mutex_init(&data->mutex_printf, NULL);
	// while (1)
	// {
	// 	n = data->n;
	// 	while (n)
	// 	{
	// 		if (is_dead(data, data->plist))
	// 		{
	// 			data->must_die = 1;
	// 			join_all_threads(plist);
	// 			destroy_all_mutex(plist);
	// 			return(exit_phylo(data, 0));
	// 		}
	// 		data->plist = plist->next;
	// 		n++;
	// 	}
	// 	for (philo in philosophers)
	// }
	return (0);
}

/*


*/