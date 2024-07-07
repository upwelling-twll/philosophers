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

#include "../phylosopher.h"

int	eating_routine(t_phlst *philo, t_param *shared_data)
{
	struct timeval	cur_time;

	pthread_mutex_lock(&(philo->philo_mutex));
	philo->is_eating = 1;
	pthread_mutex_unlock(&(philo->philo_mutex));
	pthread_mutex_lock(&shared_data->mutex_printf);
	print_action(philo->index, 1, shared_data); //eating
	pthread_mutex_unlock(&shared_data->mutex_printf);
		// pthread_mutex_lock(&shared_data->mutex_printf);
		// printf("said i am eating N=%i \n", philo->index); //took_left_fork
		// pthread_mutex_unlock(&shared_data->mutex_printf);
	pthread_mutex_lock(&(philo->philo_mutex));
	gettimeofday(&cur_time, NULL);
	philo->lst_eating_time = cur_time;
	// pthread_mutex_unlock(&(philo->philo_mutex));
	// pthread_mutex_lock(&(philo->philo_mutex));
	philo->turns ++;
	pthread_mutex_unlock(&(philo->philo_mutex));
		// pthread_mutex_lock(&shared_data->mutex_printf);
		// printf("updated time and turns N=%i \n", philo->index); //took_left_fork
		// pthread_mutex_unlock(&shared_data->mutex_printf);
	my_usleep(shared_data->time_to_eat, shared_data, philo->index); //usleep(shared_data->time_to_eat);
	
			// pthread_mutex_lock(&shared_data->mutex_printf);
			// print_action(philo->index, 13, shared_data);
			// pthread_mutex_unlock(&shared_data->mutex_printf);
	// this modifies object fork, not philo
	// both forks are already locked in taking_forks
	philo->left_fork->last_user = philo->index;
	philo->right_fork->last_user = philo->index;
	pthread_mutex_unlock(min_fork(philo));
	pthread_mutex_unlock(max_fork(philo));
	
	// struct timeval	time_now;
	// gettimeofday(&time_now, NULL);
	//  printf("after eating - %li\n", ((time_now.tv_sec * 1000000 + time_now.tv_usec)));

	// pthread_mutex_lock(&shared_data->mutex_printf);
	// printf("left usleep condition N=%i \n", philo->index); //took_left_fork
	// pthread_mutex_unlock(&shared_data->mutex_printf);

	// pthread_mutex_unlock(min_fork(philo));
	// pthread_mutex_unlock(max_fork(philo));
		// pthread_mutex_lock(&(*(philo->param))->mutex_printf);
		// printf("Nph=%i my forks are free\n", philo->index);
		// pthread_mutex_unlock(&(*(philo->param))->mutex_printf);
	pthread_mutex_lock(&(philo->philo_mutex));
	philo->is_eating = 0;
	pthread_mutex_unlock(&(philo->philo_mutex));
	return (0);
}

int	taking_forks(t_phlst *p, t_param *sd, pthread_mutex_t sd_mutex)
{
	long long i = 0;
	pthread_mutex_t	*fork1_mutex;
	pthread_mutex_t	*fork2_mutex;

	while (min_frk_lst_usr(p) == p->index || max_frk_lst_usr(p) == p->index)
	{
		usleep(100);
		i++;
		pthread_mutex_lock(&sd->mutex_printf);
		print_action(p->index, 20, sd);
		pthread_mutex_unlock(&sd->mutex_printf);
		// pthread_mutex_lock(&sd->param_mutex);
		// sd->prog_must_die = 1;
		// pthread_mutex_unlock(&sd->param_mutex);
		// return (1);
	}
		// pthread_mutex_lock(&sd->mutex_printf);
		// print_action(p->index, 16, sd); //checking forks
		// pthread_mutex_unlock(&sd->mutex_printf);
	// if (someone_is_dead(sd, sd_mutex))
	// 	return (1);
		// pthread_mutex_lock(&sd->mutex_printf);
		// printf("	Ph num=%i: will take first fork\n", p->index);
		// pthread_mutex_unlock(&sd->mutex_printf);
	if (sd->n % 2 != 0)
	{
		fork1_mutex = min_fork(p);
		fork2_mutex = max_fork(p);
	}
	else
	{
		fork1_mutex = max_fork(p);
		fork2_mutex = min_fork(p);
	}
	pthread_mutex_lock(fork1_mutex);
	pthread_mutex_lock(&sd->mutex_printf);
	print_action((p)->index, 4, sd); //took_left_fork
	pthread_mutex_unlock(&sd->mutex_printf);
		// printf("fork_is = %i\n", first_frk_id(p));
	
	if (someone_is_dead(p->index, sd, sd_mutex))
	{
		pthread_mutex_unlock(fork1_mutex);
		return (1);
	}
	pthread_mutex_lock(fork2_mutex);
	pthread_mutex_lock(&sd->mutex_printf);
	print_action((p)->index, 4, sd); //took_left_fork
	pthread_mutex_unlock(&sd->mutex_printf);
	return (0);
}
