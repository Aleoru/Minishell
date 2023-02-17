/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:42:46 by aoropeza          #+#    #+#             */
/*   Updated: 2022/04/27 20:09:00 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	index_dest;
	size_t	index_src;

	index_dest = 0;
	index_src = 0;
	while (dest[index_dest])
		index_dest++;
	if (size < index_dest)
	{
		while (src[index_src])
			index_src++;
		return (size + index_src);
	}
	while (size > 0 && index_dest < size - 1 && src[index_src])
	{
		dest[index_dest] = src[index_src];
		index_dest++;
		index_src++;
	}
	dest[index_dest] = '\0';
	while (src[index_src++])
		index_dest++;
	return (index_dest);
}
