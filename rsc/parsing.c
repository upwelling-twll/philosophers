/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/04 15:24:09 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phylosopher.h"

int	incorrect_data(t_param *data)
{
	int	eat;
	int	die;
	int	sleep;
	int	n;

	eat = data->time_to_eat;
	die = data->time_to_die;
	sleep = data->time_to_sleep;
	n = data->n;
	if (!(eat > 0 && die > 0 && sleep > 0 && n > 0 && data->turns_to_eat >= 0))
		return (1);
	// printf("n = %i\n", n);
	if (n > 200 )
		return (1);
	return (0);
}

void	proc_first_four_args(t_param *data, char **argv)
{
	data->n = atoi(argv[1]);
	data->time_to_eat = atoi(argv[3]) * 1000;
	data->time_to_die = atoi(argv[2]) * 1000;
	data->time_to_sleep = atoi(argv[4]) * 1000;
}

t_param	*parsing(int argc, char **argv)
{
	t_param	*data;

	data = NULL;
	if (argc < 5 || !argv)
		return (NULL);
	data = malloc(sizeof(t_param));
	proc_first_four_args(data, argv);
	if (argv[5])
	{
		if (atoi(argv[5]) == 0)
		{
			free(data);
			return (NULL);
		}
		data->turns_to_eat = atoi(argv[5]);
	}
	else
		data->turns_to_eat = 0;
	if (incorrect_data(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
}
