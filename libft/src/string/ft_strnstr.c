/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:29:39 by aoropeza          #+#    #+#             */
/*   Updated: 2022/04/28 17:56:51 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int	index_one;
	unsigned int	index_two;

	index_one = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[index_one] && index_one < len)
	{
		index_two = 0;
		while (str[index_one + index_two] != '\0' && str[index_one + index_two]
			== to_find[index_two] && index_one + index_two < len)
		{
			if (to_find[index_two + 1] == '\0')
				return ((char *)&str[index_one]);
			index_two++;
		}
		index_one++;
	}
	return (0);
}
