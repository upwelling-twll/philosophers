/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 17:00:02 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

long	print_time(t_param *data)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);

	// printf("%li.%li ", ((time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
	// 		- (data->prog_start.tv_sec * 1000 + data->prog_start.tv_usec / 1000)),
	// 		((time_now.tv_sec * 1000 * 1000 + time_now.tv_usec)
	// 		- (data->prog_start.tv_sec * 1000 * 1000 + data->prog_start.tv_usec)) % 1000); 

	// correct outpuc according to sbj
	return(((time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
			- (data->prog_start.tv_sec * 1000 + data->prog_start.tv_usec / 1000))); 
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
	timestamp = print_time(data);

	// for debug
	struct timeval  time_now;
	long time1, time2;

	gettimeofday(&time_now, NULL);

	time1 = ((time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
			- (data->prog_start.tv_sec * 1000 + data->prog_start.tv_usec / 1000));
	time2 = ((time_now.tv_sec * 1000 * 1000 + time_now.tv_usec)
			- (data->prog_start.tv_sec * 1000 * 1000 + data->prog_start.tv_usec)) % 1000;
	// if (someone_is_dead(n, data, data->param_mutex))
	// 	return (NULL);
	pthread_mutex_lock(&data->mutex_printf);
	printf("%li.%li %i %s ", time1, time2, n, message); 
	// printf("%li %i %s", timestamp, n, message);
	pthread_mutex_unlock(&data->mutex_printf);
	return (NULL);
}
