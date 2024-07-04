/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 14:06:45 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

int	sleeping_routine(t_phlst *philo, t_param *shared_data)
{
	pthread_mutex_lock(&shared_data->mutex_printf);
	print_action(philo->index, 2, shared_data); //sleeping
	pthread_mutex_unlock(&shared_data->mutex_printf);
		//usleep(shared_data->time_to_sleep);
	if (my_usleep(shared_data->time_to_sleep, shared_data, philo->index))
		return (1);
	pthread_mutex_lock(&shared_data->mutex_printf);
	print_action(philo->index, 7, shared_data); //thinking
	pthread_mutex_unlock(&shared_data->mutex_printf);
	return (0);
}
