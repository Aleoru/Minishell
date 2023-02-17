/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:20:48 by aoropeza          #+#    #+#             */
/*   Updated: 2022/04/27 20:09:35 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *str_one, const void *str_two, size_t nb)
{
	t_size	*mem_one;
	t_size	*mem_two;
	size_t	index;

	mem_one = (t_size *)str_one;
	mem_two = (t_size *)str_two;
	index = 0;
	while (index < nb)
	{
		if (mem_one[index] != mem_two[index])
			return (mem_one[index] - mem_two[index]);
		index++;
	}
	return (0);
}
