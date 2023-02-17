/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:19:52 by aoropeza          #+#    #+#             */
/*   Updated: 2022/04/27 20:08:40 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t nb)
{
	const char		*str_src;
	unsigned char	*str_dest;
	size_t			index;

	index = 0;
	str_src = (const char *)src;
	str_dest = (unsigned char *)dest;
	while (index < nb)
	{
		if (dest < src)
			str_dest[index] = str_src[index];
		else if (dest > src)
			str_dest[nb - index - 1] = str_src[nb - index - 1];
		index++;
	}
	return (dest);
}
