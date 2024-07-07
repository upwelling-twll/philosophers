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
	if (action == 9)
		message = "done eating\n";
	if (action == 10)
		message = "is no more using a min fork\n";
	if (action == 11)
		message = "is no more using max fork\n";
	if (action == 12)
		message = "done thinking\n";
	if (action == 13)
		message = "ended usleep as smn is dead\n";
	if (action == 14)
		message = "usleep is going to start\n";
	if (action == 15)
		message = "usleep time target achived:";
	if (action == 16)
		message = "ready to check forks\n";
	if (action == 17)
		message = "will check odd even\n";
	if (action == 18)
		message = "unlocked my forks\n";
	if (action == 19)
		message = "                      checking smn is dead\n";
	if (action == 20)
		message = "last user of fork is me\n";
	timestamp = print_time(data);

	// for debug
	struct timeval  time_now;
	long time1, time2;

	gettimeofday(&time_now, NULL);

	time1 = ((time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
			- (data->prog_start.tv_sec * 1000 + data->prog_start.tv_usec / 1000));
	time2 = ((time_now.tv_sec * 1000 * 1000 + time_now.tv_usec)
			- (data->prog_start.tv_sec * 1000 * 1000 + data->prog_start.tv_usec)) % 1000;

	pthread_mutex_lock(&data->mutex_printf);
	printf("%li.%li %i %s ", time1, time2, n, message); 
	// printf("%li %i %s", timestamp, n, message);
	pthread_mutex_unlock(&data->mutex_printf);
	return (NULL);
}
