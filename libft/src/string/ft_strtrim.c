/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:42:53 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/10 18:16:29 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*aux;
	size_t		index_str;
	size_t		len;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	index_str = 0;
	while (s1[index_str] && ft_strchr(set, s1[index_str]))
		index_str++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len]))
		len--;
	aux = ft_substr(s1, index_str, len - index_str + 1);
	return (aux);
}
