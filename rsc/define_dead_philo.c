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

int	is_dead_signal(t_param *data, t_phlst *philo)
{
	pthread_mutex_lock(&(data->param_mutex));
	data->prog_must_die = 1;
	pthread_mutex_unlock(&(data->param_mutex));
	pthread_mutex_lock(&(data->mutex_printf));
	print_action(philo->index, 6, *(philo->param));
	pthread_mutex_unlock(&(data->mutex_printf));
	return (1);
}

int	is_dead(t_param *data, t_phlst *philo)
{
	size_t			time_after_eating;
	struct timeval	cur;

	if (philo->turns == 0)
		return (0);
	gettimeofday(&cur, NULL);
	time_after_eating = (cur.tv_sec - philo->lst_eating_time.tv_sec) 
		* 1000000 + (cur.tv_usec - philo->lst_eating_time.tv_usec);
	pthread_mutex_lock(&(philo->philo_mutex));
	if (philo->is_eating == 1)
	{
		pthread_mutex_unlock(&(philo->philo_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philo->philo_mutex));
	if (time_after_eating > data->time_to_die)
	{
		return (is_dead_signal(data, philo));
	}
	return (0);
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
