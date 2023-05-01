/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:22:47 by aoropeza          #+#    #+#             */
/*   Updated: 2023/04/28 20:22:49 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_env_paths(t_mini *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	while (mini->env[i])
	{
		tmp = ft_strnstr(mini->env[i], "PATH=", ft_strlen("PATH="));
		if (tmp)
		{
			tmp = ft_strdup(mini->env[i]);
			break ;
		}
		i++;
	}
	mini->paths = ft_split(tmp, ':');
	i = 0;
	while (mini->paths[i])
	{
		free(tmp);
		tmp = mini->paths[i];
		mini->paths[i] = ft_strjoin(tmp, "/");
		i++;
	}
	mini->paths[i] = NULL;
	free(tmp);
}

void	exit_error(char *error)
{
	perror(error);
	return ;
}

static char	*get_cmd_path(char *cmd, t_mini *mini)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (mini->paths[++i])
	{
		cmd_path = ft_strjoin(mini->paths[i], cmd);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		free (cmd_path);
	}
	return (0);
}

void	exec_cmd(t_mini mini, char *str)
{
	char	*cmd_path;

	mini.options = ft_split(str, ' ');
	mini.cmd = ft_strdup(mini.options[0]);
	cmd_path = get_cmd_path(mini.cmd, &mini);
	if (!cmd_path)
		exit_error(ERROR_CMD);
	if (execve(cmd_path, mini.options, mini.env))
	{
		write(2, "ERROR", ft_strlen("ERROR"));
		write(2, "\n", 1);
	}
	return ;
}
