/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:14:23 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/06 17:58:57 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int	index;

	index = 0;
	while (str[index] != (char)ch)
	{
		if (!str[index])
			return (0);
		index++;
	}
	return ((char *)&str[index]);
}
