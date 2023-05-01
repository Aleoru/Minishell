/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:55:06 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/04/14 18:55:08 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	unset(t_mini *mini, char *var_name)
{
	char	*expand;

	expand = expand_var(var_name, mini->var);
	if (expand)
	{
		free(expand);
		mini->var = del_var(mini->var, var_name, mini->var_len);
		mini->var_len--;
		expand = expand_var(var_name, mini->env);
		if (expand)
		{
			free(expand);
			mini->env = del_var(mini->env, var_name, mini->env_len);
			mini->env_len--;
		}
		return (0);
	}
	return (1);
}

int	built_unset(t_mini *mini)
{
	int		i;

	i = 1;
	while (mini->options[i])
	{
		unset(mini, mini->options[i]);
		i++;
	}
	return (0);
}

char	**del_var(char **src, char *var_name, int len)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc((sizeof(char *) * len) + 1);
	while (src[i])
	{
		if (!contain_var(src, var_name, i))
		{
			new[j] = ft_strdup(src[i]);
			j++;
			i++;
		}
		else
			i++;
	}
	new[j] = NULL;
	free_split(src);
	return (new);
}
