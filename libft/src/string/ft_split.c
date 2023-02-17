/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:47:39 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/10 18:14:31 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	**split_free(char **array)
{
	size_t	elem;

	elem = 0;
	while (array)
	{
		free(array[elem]);
		elem++;
	}
	free (array);
	return (NULL);
}

static size_t	count_word(char const *str, char c)
{
	size_t	index;
	size_t	elem;

	index = 0;
	elem = 0;
	while (str[index] == c)
		index++;
	while (str[index])
	{
		if (str[index] == c && str[index + 1] != c && str[index + 1] != '\0')
			elem++;
		index++;
	}
	return (elem + 1);
}

char	**ft_split(char const *str, char c)
{
	char	**array;
	size_t	elem;
	size_t	str_pos;
	size_t	start;

	if (str == NULL)
		return (NULL);
	array = malloc((count_word(str, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	str_pos = 0;
	elem = 0;
	while (str[str_pos] && elem < count_word(str, c))
	{
		while (str[str_pos] == c && str[str_pos] != '\0')
			str_pos++;
		start = str_pos;
		while (str[str_pos] != c && str[str_pos] != '\0')
			str_pos++;
		array[elem++] = ft_substr(str, start, (str_pos - start));
		if (!array[elem - 1])
			return (split_free(array));
	}
	array[elem] = 0;
	return (array);
}
