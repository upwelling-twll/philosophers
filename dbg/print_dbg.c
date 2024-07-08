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

#include "../philosopher.h"

/* for millisec.microsec output

	struct timeval  time_now;
	long time1, time2;

	gettimeofday(&time_now, NULL);

	time1 = ((time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
			- (data->prog_start.tv_sec * 1000 + data->prog_start.tv_usec / 1000));
	time2 = ((time_now.tv_sec * 1000 * 1000 + time_now.tv_usec)
			- (data->prog_start.tv_sec * 1000 * 1000 + data->prog_start.tv_usec)) % 1000;
	pthread_mutex_lock(&data->mutex_printf);
	printf("%li.%li %i %s ", time1, time2, n, message); 
	pthread_mutex_unlock(&data->mutex_printf);
*/

void	*action_dbg(int action)
{
	if (action == 9)
		return ("done eating\n");
	if (action == 10)
		return ("is no more using a min fork\n");
	if (action == 11)
		return ("is no more using max fork\n");
	if (action == 12)
		return ("done thinking\n");
	if (action == 13)
		return ("ended usleep as smn is dead\n");
	if (action == 14)
		return ("usleep is going to start\n");
	if (action == 15)
		return ("usleep time target achived:");
	if (action == 16)
		return ("ready to check forks\n");
	if (action == 17)
		return ("will check odd even\n");
	if (action == 18)
		return ("unlocked my forks\n");
	if (action == 19)
		return ("                      checking smn is dead\n");
	if (action == 20)
		return ("last user of fork is me\n");
	return (NULL);
}
