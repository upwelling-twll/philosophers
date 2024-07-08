/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 17:17:45 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static int	check_odd_even(t_phlst *ph)
{
	if (ph->index % 2 == 0)
		usleep(15000);
	return (0);
}

int	thinking_routine(t_phlst *p, t_param *sd)
{
	print_action(p->index, 7, sd);
	return (0);
}

int	philo_routine(t_phlst *p, t_param *sd, pthread_mutex_t sd_mutex)
{
	if (p->turns == 0 && check_odd_even(p))
		return (1);
	if (taking_forks(p, sd, sd_mutex))
		return (1);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	if (eating_routine(p, sd))
		return (1);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	if (sleeping_routine(p, sd))
		return (1);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	if (thinking_routine(p, sd))
		return (1);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	return (0);
}
