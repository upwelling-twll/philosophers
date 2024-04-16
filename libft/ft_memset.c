/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:44:28 by nmagdano          #+#    #+#             */
/*   Updated: 2023/07/09 13:44:31 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	h;

	str = (unsigned char *)b;
	h = (unsigned char)c;
	printf("memset len = %zu\n", len);
	while (len--)
	{
		*str = h;
		str++;
		//printf("memset len = %zu\n", len);
	}
	return (b);
}
