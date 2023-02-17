/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:57:59 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/10 18:17:00 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	index;

	index = 0;
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[start] && index < len)
	{
		str[index] = s[start];
		start++;
		index++;
	}
	str[index] = '\0';
	return (str);
}
