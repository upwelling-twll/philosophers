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

void	destroy_all_mutex(t_param *data, t_fork **forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(data->param_mutex));
	pthread_mutex_destroy(&(data->mutex_printf));
	while (i < data->n)
	{
		pthread_mutex_destroy(&(forks[i]->fork_mutex));
		i++;
	}
}

void	clean_plist_and_forks(t_param *data)
{
	int		i;
	t_fork	**forks;
	t_phlst	**philos;

	i = 0;
	forks = data->forks;
	philos = data->plist;
	while (i < data->n)
	{
		free(forks[i]);
		i++;
	}
	i = 0;
	while (i < data->n)
	{
		free(philos[i]);
		i++;
	}
}

int	exit_phylo(t_param *data, int flag)
{
	if (flag == 2)
		printf("Invalid parameters\n");
	if (flag == 1)
		printf("Program exit\n");
	if (data && data ->prog_must_die == 1)
		printf("Someone is dead\n");
	if (flag != 2)
		clean_plist_and_forks(data);
	if (data != NULL)
		free(data);
	return (1);
}
