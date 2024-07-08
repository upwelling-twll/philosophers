/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/02 17:21:29 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long long	timestamp(void)
{
	struct timeval	timestrc;

	gettimeofday(&timestrc, NULL);
	return ((timestrc.tv_sec * 1000) + (timestrc.tv_usec / 1000));
}

long long	time_diff(long long past, long long present)
{
	return (present - past);
}

int	prog_end(t_param *data)
{
	pthread_mutex_lock(&(data->param_mutex));
	if (data->prog_must_die == 1)
	{
		pthread_mutex_unlock(&(data->param_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->param_mutex));
	return (0);
}

int	my_usleep(long long time, t_param *data)
{
	long long	start;
	long long	sleep_time;
	long long	diff;

	time /= 1000;
	start = timestamp();
	sleep_time = 900 * time;
	usleep(sleep_time);
	while (!(someone_is_dead(data, data->param_mutex)))
	{
		diff = time_diff(start, timestamp());
		if (diff >= time)
			return (0);
		usleep(100);
	}
	return (1);
}
