/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_structures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 14:19:00 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

void	print_philo_struct(t_phlst *plist)
{
	printf("Philo index %i; ", plist->index);
	printf("last_eating_time %li; ", plist->lst_eating_time.tv_sec);
	printf("Left fork %i; ", plist->left_fork->fork);
	printf("Right fork %i; ", plist->right_fork->fork);
	printf("must die %i.\n", plist->must_die);
}

void	print_data_list(t_param *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		print_philo_struct(data->plist[i]);
		i++;
	}
}

int	min_frk_id(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork < one_philo->right_fork->fork)
		return (one_philo->left_fork->fork);
	else
		return (one_philo->right_fork->fork);
}

int	max_frk_id(t_phlst *one_philo)
{
	if (one_philo->left_fork->fork > one_philo->right_fork->fork)
		return (one_philo->left_fork->fork);
	else
		return (one_philo->right_fork->fork);
}
