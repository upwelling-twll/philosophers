/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/09 15:43:20 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	init_forks(t_fork **forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		forks[i] = (t_fork *)malloc(sizeof(t_fork));
		forks[i]->fork = i + 1;
		forks[i]->last_user = 0;
		pthread_mutex_init(&(forks[i]->fork_mutex), NULL);
		i++;
	}
}

t_phlst	*init_plist_and_forks(t_phlst **plist, int n, t_fork **forks)
{
	int	i;

	i = 0;
	init_forks(forks, n);
	while (i < n)
	{
		plist[i] = (t_phlst *)malloc(sizeof(t_phlst));
		plist[i]->index = i + 1;
		plist[i]->must_die = 0;
		plist[i]->turns = 0;
		plist[i]->is_eating = 0;
		pthread_mutex_init(&plist[i]->philo_mutex, NULL);
		if (i != n - 1)
		{
			plist[i]->left_fork = forks[i];
			plist[i]->right_fork = forks[i + 1];
		}
		else
		{
			plist[i]->left_fork = forks[i];
			plist[i]->right_fork = forks[0];
		}
		i++;
	}
	return (*plist);
}

void	init_data(t_phlst **plist, t_param *data, t_fork **forks)
{
	struct timeval	start;

	init_plist_and_forks(plist, data->n, forks);
	data->plist = plist;
	data->forks = forks;
	pthread_mutex_init(&data->mutex_printf, NULL);
	pthread_mutex_init(&data->param_mutex, NULL);
	data->prog_must_die = 0;
	gettimeofday(&start, NULL);
	data->prog_start = start;
}
