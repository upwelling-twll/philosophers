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

int	min_frk_lst_usr(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork < one_philo->right_fork->fork)
		return (one_philo->left_fork->last_user);
	else
		return (one_philo->right_fork->last_user);
}

int	max_frk_lst_usr(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork > one_philo->right_fork->fork)
		return (one_philo->left_fork->last_user);
	else
		return (one_philo->right_fork->last_user);
}

pthread_mutex_t	*min_fork(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork < one_philo->right_fork->fork)
		return (&one_philo->left_fork->fork_mutex);
	else
		return (&one_philo->right_fork->fork_mutex);
}

pthread_mutex_t	*max_fork(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork > one_philo->right_fork->fork)
		return (&one_philo->left_fork->fork_mutex);
	else
		return (&one_philo->right_fork->fork_mutex);
}
