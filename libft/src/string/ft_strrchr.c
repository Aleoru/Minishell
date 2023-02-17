/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:25:53 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/10 18:16:07 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int ch)
{
	int		index;
	char	*str;

	str = (char *)s;
	index = ft_strlen(str);
	if ((char)ch == '\0')
		return (str + index);
	while (index + 1 > 0)
	{
		if (str[index] == (char)ch)
			return ((char *)&str[index]);
		index--;
	}
	return (NULL);
}
