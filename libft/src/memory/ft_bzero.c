/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:55:29 by aoropeza          #+#    #+#             */
/*   Updated: 2022/04/20 14:42:48 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_bzero(void *str, size_t nb)
{
	unsigned char	*dstr;
	size_t			index;

	dstr = str;
	index = 0;
	while (index < nb)
	{
		dstr[index] = '\0';
		index++;
	}
}
