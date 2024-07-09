/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/09 17:55:52 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long	print_time(t_param *data)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (((time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
			- (data->prog_start.tv_sec * 1000
				+ data->prog_start.tv_usec / 1000)));
}

void	*print_action(int n, int action, t_param *data)
{
	char			*message;
	long			timestamp;

	if (action == 1)
		message = "is eating\n";
	if (action == 2)
		message = "is sleeping\n";
	if (action == 3)
		message = "is dead\n";
	if (action == 4 || action == 5)
		message = "has taken a fork\n";
	if (action == 6)
		message = "died\n";
	if (action == 7)
		message = "is thinking\n";
	pthread_mutex_lock(&data->mutex_printf);
	if (someone_is_dead(data, &data->param_mutex) && (action != 6))
	{
		pthread_mutex_unlock(&data->mutex_printf);
		return (NULL);
	}
	timestamp = print_time(data);
	printf("%li %i %s", timestamp, n, message);
	pthread_mutex_unlock(&data->mutex_printf);
	return (NULL);
}

/* if (someone_is_dead(data, data->param_mutex))
	return (NULL); */