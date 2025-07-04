/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/09 16:30:07 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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
				join_all_threads(data, data->n);
				return (1);
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
				join_all_threads(data, data->n);
				return (1);
			}
			i++;
		}
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
