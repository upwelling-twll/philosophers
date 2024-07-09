/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/09 17:30:30 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char *argv[])
{
	t_param	*data;

	data = parsing(argc, argv);
	if (data == NULL)
		return (exit_phylo(data, 2));
	gettimeofday(&(data->prog_start), NULL);
	create_threads(data);
	exit_phylo(data, 1);
	return (0);
}
