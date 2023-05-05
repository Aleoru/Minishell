/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:19:21 by aoropeza          #+#    #+#             */
/*   Updated: 2023/03/21 12:19:23 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc(t_mini *mini)
{
	char	*buf;

	mini->in_fd = open(mini->infile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!ft_strncmp(mini->limit, buf, ft_strlen(buf) - 1))
			break ;
		write(mini->in_fd, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	free(mini->limit);
	close(mini->in_fd);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*command;

	while (*paths)
	{
		command = ft_strjoin(*paths, cmd);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	write(2, ERROR_CMD, ft_strlen(ERROR_CMD));
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (NULL);
}

static void	waiting(int iterations)
{
	int	i;

	i = 0;
	while (i < iterations)
		i++;
}

void	seting_pipex(t_mini *mini)
{
	mini->in_fd = -2;
	mini->out_fd = -2;
	if (mini->heredoc)
	{
		mini->infile = ft_strdup("./.infile.tmp");
		heredoc(mini);
	}
	if (mini->infile != NULL)
		mini->in_fd = open(mini->infile, O_RDONLY);
	if (mini->outfile != NULL && mini->append)
		mini->out_fd = open(mini->outfile, O_APPEND | O_CREAT | O_RDWR, 0664);
	else if (mini->outfile != NULL)
		mini->out_fd = open(mini->outfile, O_TRUNC | O_CREAT | O_RDWR, 0664);
}

void	pipex(t_mini *mini)
{
	seting_pipex(mini);
	signal(SIGUSR2, SIG_IGN);
	mini->newline = 0;
	if (exe_alone_builtin(mini) == 0 && mini->cmd_pipe[0])
		exe_pipex(mini);
	signal(SIGUSR2, process_on);
	waiting(1000000);
	mini->newline = 1;
	if (mini->outfile != NULL)
	{
		close(mini->out_fd);
		free(mini->outfile);
	}
	if (mini->infile != NULL)
	{
		if (mini->heredoc)
			unlink(".infile.tmp");
		close(mini->in_fd);
		free(mini->infile);
	}
	mini->in_fd = -2;
	mini->out_fd = -2;
}
