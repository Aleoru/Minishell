/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:17:53 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/04/14 20:17:55 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*name_var(char *env_var)
{
	char	*name;
	int		i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	name = malloc(sizeof(char) * i + 1);
	i = 0;
	while (env_var[i] != '=')
	{
		name[i] = env_var[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	**add_str(char **src, char *str, int *len)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (*len + 2) + 1);
	while (src[i])
	{
		new[i] = ft_strdup(src[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	i++;
	new[i] = NULL;
	free_split(src);
	*len += 1;
	return (new);
}

int	contain_var(char **src, char *env_var, int i)
{
	char	*name;
	char	*tmp;

	tmp = name_var(src[i]);
	name = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = ft_strjoin(env_var, "=");
	if (ft_strnstr(name, tmp, ft_strlen(tmp)) == NULL)
	{
		free(tmp);
		free(name);
		return (0);
	}
	free(tmp);
	free(name);
	return (1);
}

void	change_value(char **src, char *new_value)
{
	int		i;
	char	*name;
	char	*expand;

	i = 0;
	name = name_var(new_value);
	expand = expand_var(name, src);
	if (expand)
	{
		free(expand);
		while (src[i])
		{
			if (contain_var(src, name, i))
			{
				free(src[i]);
				src[i] = ft_strdup(new_value);
			}
			i++;
		}
	}
	free(name);
}
