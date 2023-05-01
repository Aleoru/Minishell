/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:11:40 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/05/01 17:11:45 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	first_word(char *str1, char *str2)
{
	int		i;
	int		len1;
	int		len2;

	i = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (len1 > len2)
		return (1);
	else if (len1 < len2)
		return (-1);
	else
		return (0);
}

void	sort_strings(char **split)
{
	int		i;
	int		j;
	int		res;
	char	*str;

	i = 0;
	while (split[i])
	{
		str = split[i];
		j = i;
		while (split[j])
		{
			res = first_word(str, split[j]);
			if (res > 0)
			{
				str = split[j];
				split[j] = split[i];
				split[i] = str;
			}
			j++;
		}
		i++;
	}
}

int	split_len(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	**cpy_split(char **split)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (split_len(split) + 1) + 1);
	while (split[i])
	{
		new[i] = ft_strdup(split[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
