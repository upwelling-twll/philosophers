/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/04/04 14:28:47 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

int	min_frk_lst_usr(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork < one_philo->right_fork->fork)
		return (one_philo->left_fork->last_user);
	else
		return (one_philo->right_fork->last_user);
}

int	max_frk_lst_usr(t_phlst *one_philo)
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

int	phylosophers_act(t_param *data, t_fork **forks)
{
	int				i;
	t_phlst			*philo[200];

	i = 0;
	init_data(philo, data, forks);
	while (i < data->n)
	{
		data->plist[i]->param = &data;
		data->plist[i]->lst_eating_time = data->prog_start;
		pthread_create(&data->plist[i]->thread, NULL, philo, 
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