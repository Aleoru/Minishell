/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:43:02 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/06 18:43:53 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t nb)
{
	char	*mem_dest;
	char	*mem_src;
	size_t	index;

	mem_dest = (char *)dest;
	mem_src = (char *)src;
	index = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (index < nb)
	{
		mem_dest[index] = mem_src[index];
		index++;
	}
	return (dest);
}
