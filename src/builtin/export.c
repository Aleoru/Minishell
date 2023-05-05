/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:01:21 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/04/14 19:01:23 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_var_value(char *str)
{
	int		value;
	int		i;

	i = 0;
	value = 0;
	write(1, "declare -x ", 12);
	while (str[i])
	{
		write(1, &str[i], 1);
		if (str[i] == '=' && value == 0)
		{
			value = 1;
			write(1, "\"", 1);
		}
		i++;
	}
	if (value == 1)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

static void	print_all_env(char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = cpy_split(env);
	sort_strings(tmp);
	while (tmp[i])
	{
		print_var_value(tmp[i]);
		i++;
	}
	free_split(tmp);
}

static void	add_local(t_mini *mini, int i)
{
	char	*name;
	char	*expand;

	if (ft_strchr(mini->options[i], '=') && ft_isalpha(mini->options[i][0]))
	{
		enter_var(mini, mini->options[i]);
		name = name_var(mini->options[i]);
		free(mini->options[i]);
		mini->options[i] = name;
	}
	else if (ft_isalpha(mini->options[i][0]))
	{
		expand = expand_var(mini->options[i], mini->var);
		if (expand == NULL)
		{
			name = ft_strjoin(mini->options[i], "=");
			mini->var = add_str(mini->var, name, &mini->var_len);
			free(name);
		}
		else
			free(expand);
	}
}

int	built_export(t_mini *mini)
{
	int		i;

	i = 1;
	if (get_argc(mini) == 1)
		print_all_env(mini->env);
	else if (get_argc(mini) >= 2)
	{
		while (mini->options[i])
		{
			add_local(mini, i);
			export(mini, mini->options[i]);
			i++;
		}
	}
	return (0);
}

int	export(t_mini *mini, char *var_name)
{
	char	*expvar;
	char	*expenv;
	char	*enter_var;
	int		i;

	i = 0;
	expvar = expand_var(var_name, mini->var);
	expenv = expand_var(var_name, mini->env);
	if (expvar && expenv == NULL)
	{
		free (expvar);
		while (mini->var[i])
		{
			if (contain_var(mini->var, var_name, i))
				enter_var = ft_strdup(mini->var[i]);
			i++;
		}
		mini->env = add_str(mini->env, enter_var, &mini->env_len);
		free(enter_var);
		return (0);
	}
	if (expenv)
		free(expvar);
	free(expenv);
	return (1);
}
