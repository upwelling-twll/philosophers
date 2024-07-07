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

#include "../phylosopher.h"

static int	check_odd_even(t_phlst *ph, t_param *sd, pthread_mutex_t sd_mutex)
{
	// if (ph->turns != 0)
	// {
	// 	if (someone_is_dead(sd, sd_mutex))
	// 		return (1);

	// 	print_action(ph->index, 7, sd); //thinking

	// 	my_usleep(50, sd, ph->index);
	// }

	// print_action(ph->index, 17, sd); //will check odd even

	if (ph->index % 2 == 0)
	{
		//usleep(2500);
		// pthread_mutex_lock(&sd->mutex_printf);
		// printf("Nph=%i sent to sleep 2500", ph->index); //thinking
		// pthread_mutex_unlock(&sd->mutex_printf);
		usleep(15000);
		// if (my_usleep(100, sd, ph->index))
		// 	return (1);
	}

	// print_action(ph->index, 16, sd); //ready to check frks
	
	return (0);
}

int	thinking_routine(t_phlst *p, t_param *sd)
{
	
	print_action(p->index, 7, sd); //thinking

}

int	philo_routine(t_phlst *p, t_param *sd, pthread_mutex_t sd_mutex)
{
	if (p->turns == 0 && check_odd_even(p, sd, sd_mutex))
		return (1);
	// if (p->index == 3)
	// {
		// pthread_mutex_lock(&sd->mutex_printf);
		// printf("hello, i am number 3 and i am going to check forks\n"); //showing n 3
		// pthread_mutex_unlock(&sd->mutex_printf);
	// }
	if (taking_forks(p, sd, sd_mutex))
		return (1);
	if (someone_is_dead(p->index, sd, sd_mutex))
		return (1);
	if (eating_routine(p, sd))
		return (1);
		// pthread_mutex_lock(&sd->mutex_printf);
		// printf("finished eating, but frks my be lcked - philo N=%i \n", p->index); //took_left_fork
		// pthread_mutex_unlock(&sd->mutex_printf);
		
		// print_action(p->index, 18, sd); //unlocked my forks
	
	if (someone_is_dead(p->index, sd, sd_mutex))
		return (1);
	if (sleeping_routine(p, sd))
		return (1);
	if (someone_is_dead(p->index, sd, sd_mutex))
		return (1);
	if (thinking_routine(p, sd))
		return (1);
	if (someone_is_dead(p->index, sd, sd_mutex))
		return (1);
	return (0);
}
