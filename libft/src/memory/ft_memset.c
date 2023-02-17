/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:30:45 by aoropeza          #+#    #+#             */
/*   Updated: 2022/04/20 17:37:14 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *str, int ch, size_t nb)
{
	size_t			index;
	unsigned char	*dstr;

	index = 0;
	dstr = (unsigned char *)str;
	while (nb--)
	{
		dstr[index] = ch;
		index++;
	}
	return (dstr);
}
