/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/02 16:35:24 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

long long	timestamp(void)
{
	struct timeval	timestrc;

	gettimeofday(&timestrc, NULL);
	return ((timestrc.tv_sec * 1000) + (timestrc.tv_usec / 1000));
}

long long	time_diff(long long past, long long present)
{
	
	// printf("PRES=%lli, PAST=%lli, DIFF=%lli\n",present, past, present - past);
	
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

int	my_usleep(long long time, t_param *data, int iph)
{
	long long	start;

	// printf("usleep time target: %lli\n", time);
	time /= 1000;
	// printf("usleep time target 2: %lli\n", time);
	start = timestamp();
	int i = 0;
	long long	diff;
	long long t;
	t = 0;
			// pthread_mutex_lock(&data->mutex_printf);
			// print_action(iph, 14, data); //usleep is going to start
			// printf(" target is %lli\n", time);
			// pthread_mutex_unlock(&data->mutex_printf);
	while (!(prog_end(data)))
	{
		/*
		printf("goal: %lli\n", time);
		*/
			// pthread_mutex_lock(&data->mutex_printf);
			// print_action(iph, 16, data); //usleep is going to start
			// pthread_mutex_unlock(&data->mutex_printf);
			diff = time_diff(start, timestamp());
			t++;
			if (t == 1000 || t == 500 || t == 1000 || t == 2000 || t == 3000 || (t > 1000 && t%300 == 0))
			{
				pthread_mutex_lock(&data->mutex_printf);
				printf("Nph=%i usleep did %lli turns, crr diff=%lli\n",iph, t, diff);
				pthread_mutex_unlock(&data->mutex_printf);
			}
		if (diff >= time)
		{
			pthread_mutex_lock(&data->mutex_printf);
			print_action(iph, 15, data); // usleep time target achived
			printf("Nph=%i, i = %i, time diff = %lli, time to comp with = %lli\n", iph, i, time_diff(start, timestamp()), time);
			pthread_mutex_unlock(&data->mutex_printf);
			return (0);
		}
		i++;
		usleep(50);
	}
	pthread_mutex_lock(&data->mutex_printf);
	printf("Nph=%i usleep did %lli turns and ended with number=%lli\n",iph, t, diff);
	pthread_mutex_unlock(&data->mutex_printf);
	printf("waited for %lli ms\n", time);
	return (1);
}
