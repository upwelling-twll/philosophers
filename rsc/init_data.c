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

void	init_data(t_phlst **plist, t_param *data, t_fork **forks)
{
	struct timeval	start;

	init_plist_and_forks(plist, data->n, forks);
	data->plist = plist;
	data->forks = forks;
	pthread_mutex_init(&data->mutex_printf, NULL);
	pthread_mutex_init(&data->param_mutex, NULL);
	data->prog_must_die = 0;
	gettimeofday(&start, NULL);
	data->prog_start = start;
}
