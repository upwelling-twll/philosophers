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

long long	timestamp(void)
{
	struct timeval	timestrc;

	gettimeofday(&timestrc, NULL);
	return ((timestrc.tv_sec * 1000) + (timestrc.tv_usec / 1000) * 1000);
}

long long	time_diff(long long past, long long present)
{
	/*
	printf("PRES=%lli, PAST=%lli, DIFF=%lli\n",present, past, present - past);
	*/
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

	time /= 1000;
	start = timestamp();
	while (!(prog_end(data)))
	{
		/*
		printf("goal: %lli\n", time);
		*/
		if (time_diff(start, timestamp()) >= time)
			return (0);
		usleep(50);
	}
	return (1);
}
