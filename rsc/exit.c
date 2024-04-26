#include "../phylosopher.h"

void	destroy_all_mutex(t_param *data, t_fork **forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(data->param_mutex));
	pthread_mutex_destroy(&(data->mutex_printf));
	while(i < data->n)
	{
		pthread_mutex_destroy(&(forks[i]->fork_mutex));
		i++;
	}
}

int	exit_phylo(t_param *data, int flag)
{
	if (data != NULL)
		free(data);
	if (flag == 2)
		write(1, "Invalid parameters\n", 20);
	if (flag == 1)
		write(1, "Program exit\n", 14);
	return (1);
}
