/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:16:06 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/05/01 17:16:08 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	valid_builtin(char *option, char *word)
{
	unsigned int	len;

	len = ft_strlen(word);
	if (!ft_strncmp(option, word, len) && ft_strlen(option) == len)
		return (1);
	return (0);
}

static int	exe_builtin(t_mini *mini)
{
	if (valid_builtin(mini->options[0], "env"))
		built_env(mini);
	if (valid_builtin(mini->options[0], "pwd"))
		built_pwd(mini);
	if (valid_builtin(mini->options[0], "echo"))
		built_echo(mini);
	return (1);
}

static void	prog_path(t_mini *mini, char *cwd)
{
	if (ft_strncmp(mini->options[0], "./", 2) == 0)
		mini->cmd = ft_strjoin(cwd, mini->options[0] + 1);
	else if (ft_strncmp(mini->options[0], "..", 2) == 0)
	{
		mini->cmd = ft_strjoin(cwd, "/");
		mini->cmd = ft_strjoin(cwd, mini->options[0]);
	}
	else if (ft_strncmp(mini->options[0], "/", 1) == 0)
		mini->cmd = ft_strdup(mini->options[0]);
	mini->options[0] = ft_strdup(ft_strrchr(mini->options[0], '/') + 1);
}

void	exe_command(t_mini *mini, char *cmd)
{
	char	cwd[1000];

	(void)cmd;
	get_env_paths(mini);
	getcwd(cwd, sizeof(cwd));
	exe_builtin(mini);
	if (ft_strchr(mini->options[0], '/'))
		prog_path(mini, cwd);
	else
	{
		mini->cmd = get_cmd(mini->paths, mini->options[0]);
		free_split(mini->paths);
	}
	if (mini->cmd != NULL)
		execve(mini->cmd, mini->options, mini->env);
	else
	{
		mini->p_exit = 1;
		exit(1);
	}
}

int	exe_alone_builtin(t_mini *mini)
{
	char	*str;

	str = NULL;
	if (mini->cmd_pipe[0])
	{
		str = ft_strdup(mini->cmd_pipe[0]);
		mini->options = cmd_split(mini, str, ' ');
		free(str);
		if (valid_builtin(mini->options[0], "exit"))
			built_exit(mini);
		if (valid_builtin(mini->options[0], "cd"))
			return (built_cd(mini), free_split(mini->options), 1);
		if (valid_builtin(mini->options[0], "unset"))
			return (built_unset(mini), free_split(mini->options), 1);
		if (valid_builtin(mini->options[0], "export"))
			return (built_export(mini), free_split(mini->options), 1);
		free_split(mini->options);
	}
	return (0);
}
