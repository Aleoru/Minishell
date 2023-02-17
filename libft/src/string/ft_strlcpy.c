/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:20:27 by aoropeza          #+#    #+#             */
/*   Updated: 2022/04/28 19:53:45 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	index;

	index = 0;
	if (size == 0)
	{
		dest[ft_strlen(src) + 1] = dest[0];
		return (ft_strlen(src));
	}
	while (src[index] && index < size - 1)
	{
		dest[index] = src[index];
		index++;
	}
	if (index < size)
		dest[index] = '\0';
	index = ft_strlen(src);
	return (index);
}
