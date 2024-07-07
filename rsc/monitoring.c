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

int	everyone_ate_turns(int turns_to_eat, t_phlst **philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_lock(&(philos[i]->philo_mutex));
		if (philos[i]->turns != turns_to_eat)
		{
			pthread_mutex_unlock(&(philos[i]->philo_mutex));
			return (0);
		}
		pthread_mutex_unlock(&(philos[i]->philo_mutex));
		i++;
	}
	return (1);
}

int	monitore_while_turns(t_param *data)
{
	int	i;

	i = 0;
	while (!(everyone_ate_turns(data->turns_to_eat, data->plist, data->n)))
	{
		i = 0;
		while (i < data->n)
		{
			if (is_dead(data, data->plist[i]))
			{
				pthread_mutex_lock(&(data->param_mutex));
				data->prog_must_die = 1;
				pthread_mutex_unlock(&(data->param_mutex));
				join_all_threads(data, data->n);
				//destroy_all_mutex(data, forks);
				return (1);
				//return(exit_phylo(data, 0));
			}
			i++;
		}
	}
	return (0);
}

int	monitore_endlessly(t_param *data)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->n)
		{
			
			if (is_dead(data, data->plist[i]))
			{
				pthread_mutex_lock(&(data->param_mutex));
				data->prog_must_die = 1;
				pthread_mutex_unlock(&(data->param_mutex));
				join_all_threads(data, data->n);
				//destroy_all_mutex(data, forks);
				return (1);
				//return(exit_phylo(data, 0));
			}
			i++;
		}
		usleep(25);
	}
	return (0);
}

int	monitore(t_param *data)
{
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
	return (0);
}
