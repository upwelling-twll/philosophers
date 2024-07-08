/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 15:32:19 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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
			return (NULL);
		l = l + k;
	}
	return (one_philo);
}

int	create_threads(t_param *data)
{
	int				i;
	t_phlst			**philo;
	t_fork			**forks;

	i = 0;
	forks = (t_fork **)malloc(sizeof(t_fork *)*(data->n));
	philo = (t_phlst **)malloc(sizeof(t_phlst *)*(data->n));
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