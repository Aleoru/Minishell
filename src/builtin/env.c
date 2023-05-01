/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:28:59 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/04/14 18:29:02 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_env(t_mini *mini)
{
	int	i;

	if (get_argc(mini) == 1)
	{
		i = 0;
		while (mini->env[i])
		{
			printf("%s\n", mini->env[i]);
			i++;
		}
	}
	else if (get_argc(mini) > 1)
	{
		write(2, "env: to many arguments\n", 24);
		free_son(mini);
		exit(1);
	}
	free_son(mini);
	exit(0);
}

void	init_env(t_mini *mini, char **envp)
{
	mini->env_len = 0;
	while (envp[mini->env_len])
		mini->env_len++;
	mini->env = malloc(sizeof(char *) * (mini->env_len + 1) + 1);
	mini->var = malloc(sizeof(char *) * (mini->env_len + 1) + 1);
	mini->env_len = 0;
	while (envp[mini->env_len])
	{
		mini->env[mini->env_len] = ft_strdup(envp[mini->env_len]);
		mini->var[mini->env_len] = ft_strdup(envp[mini->env_len]);
		mini->env_len++;
	}
	mini->env[mini->env_len] = NULL;
	mini->var[mini->env_len] = NULL;
	mini->var_len = mini->env_len;
	shell_level(mini);
}

void	shell_level(t_mini *mini)
{
	int		level;
	char	*new;
	char	*aux;
	char	*expand;

	expand = expand_var("SHLVL", mini->env);
	level = ft_atoi(expand);
	level++;
	aux = ft_itoa(level);
	new = ft_strjoin("SHLVL=", aux);
	enter_var(mini, new);
	free(aux);
	free(new);
	free(expand);
}

void	print_env(t_mini *mini)
{
	int		i;

	i = 0;
	printf("-------------- env var: \n");
	while (mini->env[i])
	{
		printf("var[%d]: %s\n", i, mini->env[i]);
		i++;
	}
	printf("-------------- local var: \n");
	i = 0;
	while (mini->var[i])
	{
		printf("var [%d]: %s\n", i, mini->var[i]);
		i++;
	}
}
