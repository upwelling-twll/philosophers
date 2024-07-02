/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/02 18:03:48 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

void	*thread_start(void *one_philo)
{
	int					l;
	int					k;
	int					turns;
	struct s_list_phylo	*ph;

	l = 0;
	ph = (struct s_list_phylo *)(one_philo);
	if ((*(ph->param))->turns_to_eat > 0)
	{
		k = 1;
		turns = (*(ph->param))->turns_to_eat;
	}
	else
	{
		k = 0;
		turns = 1;
	}
	while (l < turns)
	{
		if (philo_routine(ph, *(ph->param), (*(ph->param))->param_mutex))
		{
			pthread_mutex_lock(&(*(ph->param))->mutex_printf);
			printf("Nph=%i philo_routine returned 1\n", ph->index);
			pthread_mutex_unlock(&(*(ph->param))->mutex_printf);
			return (NULL);
		}
		l = l + k;
	}
	return (one_philo);
}

int	create_threads(t_param *data, t_fork **forks)
{
	int				i;
	t_phlst			*philo[200];

	i = 0;
	init_data(philo, data, forks);
	while (i < data->n)
	{
		data->plist[i]->param = &data;
		data->plist[i]->lst_eating_time = data->prog_start;
		pthread_create(&data->plist[i]->thread, NULL, thread_start, 
			(void *)(data->plist[i]));
		i++;
	}
	if (monitore(data))
		return (1);
	join_all_threads(data, data->n);
	destroy_all_mutex(data, forks);
	return (0);
}

/*


*/