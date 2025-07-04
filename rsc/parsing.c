/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/09 15:28:04 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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
	if (n > 200)
		return (1);
	return (0);
}

void	proc_first_four_args(t_param *data, char **argv)
{
	data->n = validate(argv[1]);
	data->time_to_eat = (validate(argv[3])) * 1000;
	data->time_to_die = (validate(argv[2])) * 1000;
	data->time_to_sleep = (validate(argv[4])) * 1000;
}

t_param	*parsing(int argc, char **argv)
{
	t_param	*data;

	data = NULL;
	if (argc < 5 || argc > 6 || !argv)
		return (NULL);
	data = malloc(sizeof(t_param));
	proc_first_four_args(data, argv);
	if (argv[5])
	{
		if (validate(argv[5]) == 0)
		{
			free(data);
			return (NULL);
		}
		data->turns_to_eat = validate(argv[5]);
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
