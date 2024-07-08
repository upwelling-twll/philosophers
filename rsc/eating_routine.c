/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 17:09:14 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	eating_routine(t_phlst *philo, t_param *shared_data)
{
	struct timeval	cur_time;

	pthread_mutex_lock(&(philo->philo_mutex));
	philo->is_eating = 1;
	gettimeofday(&cur_time, NULL);
	philo->lst_eating_time = cur_time;
	philo->turns ++;
	pthread_mutex_unlock(&(philo->philo_mutex));
	print_action(philo->index, 1, shared_data);
	my_usleep(shared_data->time_to_eat, shared_data);
	/* this modifies object fork, not philo 
	both forks are already locked in taking_forks */
	philo->left_fork->last_user = philo->index;
	philo->right_fork->last_user = philo->index;
	pthread_mutex_unlock(min_fork(philo));
	pthread_mutex_unlock(max_fork(philo));
	pthread_mutex_lock(&(philo->philo_mutex));
	philo->is_eating = 0;
	pthread_mutex_unlock(&(philo->philo_mutex));
	return (0);
}

void	set_forks(pthread_mutex_t **f1, pthread_mutex_t **f2, t_phlst *p)
{
	if ((*p->param)->n % 2 != 0)
	{
		*f1 = min_fork(p);
		*f2 = max_fork(p);
	}
	else
	{
		*f1 = max_fork(p);
		*f2 = min_fork(p);
	}
}

int	taking_forks(t_phlst *p, t_param *sd, pthread_mutex_t sd_mutex)
{
	pthread_mutex_t	*fork1_mutex;
	pthread_mutex_t	*fork2_mutex;

	while (min_frk_lst_usr(p) == p->index || max_frk_lst_usr(p) == p->index)
	{
		usleep(100);
		/*print_action(p->index, 20, sd);*/
		if (someone_is_dead(sd, sd_mutex))
			return (1);
	}
	set_forks(&fork1_mutex, &fork2_mutex, p);
	pthread_mutex_lock(fork1_mutex);
	print_action((p)->index, 4, sd);
	if (someone_is_dead(sd, sd_mutex) || sd->n == 1)
	{
		pthread_mutex_unlock(fork1_mutex);
		return (1);
	}
	pthread_mutex_lock(fork2_mutex);
	print_action((p)->index, 4, sd);
	return (0);
}
