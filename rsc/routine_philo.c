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
		if (my_usleep(2500, sd))
			return (1);
	}
	return (0);
}

static int	philo_routine(t_phlst *p, t_param *sd, pthread_mutex_t sd_mutex)
{
	if (check_odd_even(p, sd, sd_mutex))
		return (1);
	if (taking_forks(p, sd, sd_mutex))
		return (1);
	if (eating_routine(p, sd))
		return (1);
	finish_eating_turn(p);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	if (sleeping_routine(p, sd))
		return (1);
	if (someone_is_dead(sd, sd_mutex))
		return (1);
	return (0);
}

void	*philo(void *one_philo)
{
	int					l;
	int					k;
	int					turns;
	struct s_list_phylo	*ph;

	l = 0;
	ph = (struct s_list_phylo *)(one_philo);
	if ((*(ph->param))->turns_to_eat > 0)
	{
		k = 1;
		turns = (*(ph->param))->turns_to_eat;
	}
	else
	{
		k = 0;
		turns = 1;
	}
	while (l < turns)
	{
		if (philo_routine(ph, *(ph->param), (*(ph->param))->param_mutex))
			return (NULL);
		l = l + k;
	}
	return (one_philo);
}
