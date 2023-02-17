/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:30:47 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/06 20:50:00 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_one;
	size_t	len_two;
	size_t	index;

	len_one = ft_strlen(s1);
	len_two = ft_strlen(s2);
	str = (char *)malloc((len_one + len_two + 1));
	index = 0;
	if (str == NULL)
		return (NULL);
	while (s1[index])
	{
		str[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index])
	{
		str[len_one + index] = s2[index];
		index++;
	}
	str[len_one + len_two] = '\0';
	return (str);
}
