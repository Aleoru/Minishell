/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:01:24 by aoropeza          #+#    #+#             */
/*   Updated: 2022/04/21 18:36:30 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *str)
{
	char	*cstr;
	int		size;
	int		index;
	char	*p;

	index = 0;
	size = ft_strlen((char *)str);
	cstr = malloc((size + 1) * sizeof(char));
	if (cstr == NULL)
		return (NULL);
	p = cstr;
	while (str[index])
	{
		p[index] = str[index];
		index++;
	}
	p[index] = '\0';
	return (cstr);
}
