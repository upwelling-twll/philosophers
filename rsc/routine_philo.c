/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/02 18:07:46 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

static int	check_odd_even(t_phlst *ph, t_param *sd, pthread_mutex_t sd_mutex)
{
	if (ph->turns != 0)
	{
		if (someone_is_dead(sd, sd_mutex))
			return (1);
		pthread_mutex_lock(&sd->mutex_printf);
		print_action(ph->index, 7, sd); //thinking
		pthread_mutex_unlock(&sd->mutex_printf);
		usleep(50);
	}
	if (ph->index % 2 == 0)
	{
		//usleep(2500);
		// pthread_mutex_lock(&sd->mutex_printf);
		// printf("Nph=%i sent to sleep 2500", ph->index); //thinking
		// pthread_mutex_unlock(&sd->mutex_printf);
		if (my_usleep(2500, sd, ph->index))
			return (1);
	}
	return (0);
}

int	philo_routine(t_phlst *p, t_param *sd, pthread_mutex_t sd_mutex)
{
	if (check_odd_even(p, sd, sd_mutex))
		return (1);
	if (p->index == 3)
	{
		// pthread_mutex_lock(&sd->mutex_printf);
		// printf("hello, i am number 3 and i am going to check forks\n"); //showing n 3
		// pthread_mutex_unlock(&sd->mutex_printf);
	}
	if (taking_forks(p, sd, sd_mutex))
		return (1);
	if (eating_routine(p, sd))
		return (1);
		// pthread_mutex_lock(&sd->mutex_printf);
		// printf("finished eating, but frks my be lcked - philo N=%i \n", p->index); //took_left_fork
		// pthread_mutex_unlock(&sd->mutex_printf);
	finish_eating_turn(p);
		// pthread_mutex_lock(&sd->mutex_printf);
		// printf("finished eating - philo N=%i \n", p->index); //took_left_fork
		// pthread_mutex_unlock(&sd->mutex_printf);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	if (sleeping_routine(p, sd))
		return (1);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	return (0);
}
