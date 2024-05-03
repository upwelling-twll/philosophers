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

void	print_time(t_param *data)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	printf("%li ", ((time_now.tv_sec * 1000000 + time_now.tv_usec)
			- (data->prog_start.tv_sec * 1000000 
				+ data->prog_start.tv_usec)) / 1000);
}

void	*print_action(int n, int action, t_param *data)
{
	print_time(data);
	printf("%i ", n);
	if (action == 1)
		printf("is eating\n");
	if (action == 2)
		printf("is sleeping\n");
	if (action == 3)
		printf("is dead\n");
	if (action == 4 || action == 5)
		printf("has taken a fork\n");
	if (action == 6)
		printf("died\n");
	if (action == 7)
		printf("is thinking\n");
	if (action == 9)
		printf("done eating\n");
	if (action == 10)
		printf("is no more using a min fork\n");
	if (action == 11)
		printf("is no more using max fork\n");
	if (action == 12)
		printf("done thinking\n");
	return (NULL);
}
