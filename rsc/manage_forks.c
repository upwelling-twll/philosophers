/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 14:45:18 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

int	min_frk_lst_usr(t_phlst *one_philo)
{
	t_fork	*minf;
	int		lstusr;
	
	if (one_philo->left_fork->fork < one_philo->right_fork->fork)
		minf = one_philo->left_fork;
	else
		minf = one_philo->right_fork;
	pthread_mutex_lock(&(minf->fork_mutex));
	lstusr = minf->last_user;
	pthread_mutex_unlock(&(minf->fork_mutex));
	return (lstusr);
}

int	max_frk_lst_usr(t_phlst *one_philo)
{
	t_fork	*maxf;
	int		lstusr;
	
	if (one_philo->left_fork->fork > one_philo->right_fork->fork)
		maxf = one_philo->left_fork;
	else
		maxf = one_philo->right_fork;
	pthread_mutex_lock(&(maxf->fork_mutex));
	lstusr = maxf->last_user;
	pthread_mutex_unlock(&(maxf->fork_mutex));
	return (lstusr);
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
