/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/02 18:32:05 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

void	finish_eating_turn(t_phlst *philo)
{
	philo->left_fork->last_user = philo->index;
	philo->right_fork->last_user = philo->index;
	//printf("wonna free the forks\n");
	pthread_mutex_unlock(min_fork(philo));
	pthread_mutex_unlock(max_fork(philo));
	pthread_mutex_lock(&(*(philo->param))->mutex_printf);
	printf("Nph=%i my forks are free\n", philo->index);
	pthread_mutex_unlock(&(*(philo->param))->mutex_printf);
}

int	eating_routine(t_phlst *philo, t_param *shared_data)
{
	struct timeval	cur_time;

	pthread_mutex_lock(&(philo->philo_mutex));
	philo->is_eating = 1;
	pthread_mutex_unlock(&(philo->philo_mutex));
	pthread_mutex_lock(&shared_data->mutex_printf);
	print_action(philo->index, 1, shared_data); //eating
	pthread_mutex_unlock(&shared_data->mutex_printf);
	gettimeofday(&cur_time, NULL);
		// pthread_mutex_lock(&shared_data->mutex_printf);
		// printf("said i am eating N=%i \n", philo->index); //took_left_fork
		// pthread_mutex_unlock(&shared_data->mutex_printf);
	pthread_mutex_lock(&(philo->philo_mutex));
	philo->lst_eating_time = cur_time;
	pthread_mutex_unlock(&(philo->philo_mutex));
	pthread_mutex_lock(&(philo->philo_mutex));
	philo->turns ++;
	pthread_mutex_unlock(&(philo->philo_mutex));
		// pthread_mutex_lock(&shared_data->mutex_printf);
		// printf("updated time and turns N=%i \n", philo->index); //took_left_fork
		// pthread_mutex_unlock(&shared_data->mutex_printf);
	if (my_usleep(shared_data->time_to_eat, shared_data, philo->index)) //usleep(shared_data->time_to_eat);
	{
			// pthread_mutex_lock(&shared_data->mutex_printf);
			// print_action(philo->index, 13, shared_data);
			// pthread_mutex_unlock(&shared_data->mutex_printf);
		pthread_mutex_unlock(min_fork(philo));
		pthread_mutex_unlock(max_fork(philo));
			// pthread_mutex_lock(&shared_data->mutex_printf);
			// printf("my usleep ends bad - philo N=%i\n", philo->index);
			// pthread_mutex_unlock(&shared_data->mutex_printf);
		return (1);
	}
	
	// struct timeval	time_now;
	// gettimeofday(&time_now, NULL);
	//  printf("after eating - %li\n", ((time_now.tv_sec * 1000000 + time_now.tv_usec)));

	// pthread_mutex_lock(&shared_data->mutex_printf);
	// printf("left usleep condition N=%i \n", philo->index); //took_left_fork
	// pthread_mutex_unlock(&shared_data->mutex_printf);

	// pthread_mutex_unlock(min_fork(philo));
	// pthread_mutex_unlock(max_fork(philo));
	
	pthread_mutex_lock(&(philo->philo_mutex));
	philo->is_eating = 0;
	pthread_mutex_unlock(&(philo->philo_mutex));
	return (0);
}

int	taking_forks(t_phlst *p, t_param *sd, pthread_mutex_t sd_mutex)
{
	while (min_frk_lst_usr(p) == p->index || max_frk_lst_usr(p) == p->index)
		usleep(50);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	if (sd->n % 2 != 0)
		pthread_mutex_lock(min_fork(p));
	else
		pthread_mutex_lock(max_fork(p));
	pthread_mutex_lock(&sd->mutex_printf);
	print_action((p)->index, 4, sd); //took_left_fork
	pthread_mutex_unlock(&sd->mutex_printf);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	if (sd->n % 2 != 0)
		pthread_mutex_lock(max_fork((p)));
	else
		pthread_mutex_lock(min_fork((p)));
	pthread_mutex_lock(&sd->mutex_printf);
	print_action(p->index, 5, sd); //took_right_fork
	pthread_mutex_unlock(&sd->mutex_printf);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	return (0);
}
