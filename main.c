/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 13:34:20 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phylosopher.h"

int	main(int argc, char *argv[])
{
	t_param	*data;
	t_fork	*forks[200];

	data = parsing(argc, argv);
	if (data == NULL)
		return (exit_phylo(data, 2));
		printf("time_to_eat=%li\n", data->time_to_eat);
		printf("time_to_sleep=%li\n", data->time_to_sleep);
	gettimeofday(&(data->prog_start), NULL);
		printf("%li\n", (data->prog_start.tv_sec * 1000000 + data->prog_start.tv_usec));
	create_threads(data, forks);
	exit_phylo(data, 1);
		printf("the end ~para-pa-para pa!\n");
	return (0);
}
