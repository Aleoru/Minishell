/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:57:11 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/04/14 18:57:13 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_argc(t_mini *mini)
{
	int	len;

	len = 0;
	while (mini->options[len])
		len++;
	return (len);
}

char	*expand_var(char *name_var, char **env)
{
	char	*var;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(name_var, "=");
	while (env[i])
	{
		var = ft_strnstr(env[i], tmp, ft_strlen(tmp));
		if (var)
		{
			var = ft_strdup(env[i] + ft_strlen(tmp));
			break ;
		}
		i++;
	}
	free(tmp);
	return (var);
}

char	*expand_var_all(t_mini *mini, char *name_var)
{
	char	*var;

	var = expand_var(name_var, mini->env);
	if (var == NULL)
		var = expand_var(name_var, mini->var);
	return (var);
}

void	enter_var(t_mini *mini, char *enter_var)
{
	char	*name;
	char	*expand;

	name = name_var(enter_var);
	expand = expand_var(name, mini->var);
	if (expand)
	{
		change_value(mini->var, enter_var);
		free(expand);
		expand = expand_var(name, mini->env);
		if (expand)
		{
			change_value(mini->env, enter_var);
			free(expand);
		}
	}
	else
		mini->var = add_str(mini->var, enter_var, &mini->var_len);
	free(name);
}
