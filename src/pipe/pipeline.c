/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:15:31 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/05/01 17:15:34 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fd(t_mini *mini)
{
	int		i;

	i = 0;
	while (i < mini->n_cmd -1)
	{
		close(mini->fd[i][0]);
		close(mini->fd[i][1]);
		i++;
	}
}

void	dup_fd(t_mini *mini, int children)
{
	if (children == 0)
	{
		if (mini->in_fd != -2)
			dup2(mini->in_fd, STDIN_FILENO);
		if (mini->out_fd != -2 && mini->n_cmd == 1)
			dup2(mini->out_fd, STDOUT_FILENO);
		if (mini->n_cmd > 1)
			dup2(mini->fd[0][1], STDOUT_FILENO);
	}
	else if (children == mini->n_cmd -1)
	{
		if (mini->out_fd != -2)
			dup2(mini->out_fd, STDOUT_FILENO);
		dup2(mini->fd[children -1][0], STDIN_FILENO);
	}
	else
	{
		dup2(mini->fd[children][1], STDOUT_FILENO);
		dup2(mini->fd[children - 1][0], STDIN_FILENO);
	}
}

static void	wait_processes(t_mini *mini)
{
	int	state;

	waitpid(-1, &state, 0);
	mini->p_exit = WEXITSTATUS(state);
}

void	exe_pipex(t_mini *mini)
{
	int		i;

	i = 0;
	while (i < mini->n_cmd -1)
	{
		pipe(mini->fd[i]);
		i++;
	}
	i = 0;
	while (i < mini->n_cmd)
	{
		mini->options = cmd_split(mini, mini->cmd_pipe[i], ' ');
		mini->pid[i] = fork();
		if (mini->pid[i] == 0)
		{
			dup_fd(mini, i);
			close_fd(mini);
			exe_command(mini, mini->cmd_pipe[i]);
		}
		free_split(mini->options);
		i++;
	}
	close_fd(mini);
	wait_processes(mini);
}
