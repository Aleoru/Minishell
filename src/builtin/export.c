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

int	built_export(t_mini *mini)
{
	int	i;

	i = 1;
	if (get_argc(mini) >= 2)
	{
		while (mini->options[i])
		{
			export(mini, mini->options[i]);
			i++;
		}
	}
	exit(0);
}

/* Añade en env una variable que exista en var */
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
	free(expenv);
	return (1);
}
