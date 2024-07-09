/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_dead_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/09 15:51:15 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	is_dead_signal(t_param *data, t_phlst *philo)
{
	pthread_mutex_lock(&(data->param_mutex));
	data->prog_must_die = 1;
	pthread_mutex_unlock(&(data->param_mutex));
	print_action(philo->index, 6, *(philo->param));
	return (1);
}

int	is_dead(t_param *data, t_phlst *philo)
{
	size_t			time_after_eating;
	struct timeval	cur;
	t_param			*sd;

	sd = (*philo->param);
	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->is_eating)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (0);
	}
	gettimeofday(&cur, NULL);
	if (philo->turns == 0)
		time_after_eating = (cur.tv_sec - sd->prog_start.tv_sec)
			* 1000 * 1000 + (cur.tv_usec - sd->prog_start.tv_usec);
	else
		time_after_eating = (cur.tv_sec - philo->lst_eating_time.tv_sec)
			* 1000 * 1000 + (cur.tv_usec - philo->lst_eating_time.tv_usec);
	pthread_mutex_unlock(&philo->philo_mutex);
	if (time_after_eating > data->time_to_die)
		return (is_dead_signal(data, philo));
	return (0);
}

int	someone_is_dead(t_param *shared_data, pthread_mutex_t *sd_mutex)
{
	pthread_mutex_lock(sd_mutex);
	if (shared_data->prog_must_die)
	{
		pthread_mutex_unlock(sd_mutex);
		return (1);
	}
	pthread_mutex_unlock(sd_mutex);
	return (0);
}
