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

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

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

int	exe_builtin(t_mini *mini)
{
	if (ft_strncmp(mini->options[0], "env", 3) == 0
		&& ft_strlen(mini->options[0]) == 3)
		built_env(mini);
	if (ft_strncmp(mini->options[0], "pwd", 3) == 0
		&& ft_strlen(mini->options[0]) == 3)
		built_pwd(mini);
	if (ft_strncmp(mini->options[0], "echo", 4) == 0
		&& ft_strlen(mini->options[0]) == 4)
		built_echo(mini);
	return (1);
}

/* v3 builtins, ejecutables y comandos */
void	exe_command(t_mini *mini, char *cmd)
{
	char	cwd[1000];

	getcwd(cwd, sizeof(cwd));
	mini->options = cmd_split(mini, cmd, ' ');
	exe_builtin(mini);
	if (ft_strchr(mini->options[0], '/'))
	{
		if (ft_strncmp(mini->options[0], "./", 2) == 0)
		{
			mini->cmd = ft_strjoin(cwd, mini->options[0] + 1);
		}
		else if (ft_strncmp(mini->options[0], "..", 2) == 0)
		{
			mini->cmd = ft_strjoin(cwd, "/");
			mini->cmd = ft_strjoin(cwd, mini->options[0]);
		}
		else if (ft_strncmp(mini->options[0], "/", 1) == 0)
		{
			mini->cmd = ft_strdup(mini->options[0]);
		}
		mini->options[0] = ft_strdup(ft_strrchr(mini->options[0], '/') + 1);
	}
	else
		mini->cmd = get_cmd(mini->paths, mini->options[0]);
	if (mini->cmd != NULL)
	{
		execve(mini->cmd, mini->options, mini->env);
	}
	else
	{
		mini->p_exit = 1;
		exit(1);
	}
}

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

static void	waiting(int iterations)
{
	int	i;

	i = 0;
	while (i < iterations)
		i++;
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
	// signal(SIGUSR2, SIG_IGN);
	// mini->newline = 0;
	while (i < mini->n_cmd)
	{
		mini->pid[i] = fork();
		if (mini->pid[i] == 0)
		{
			dup_fd(mini, i);
			close_fd(mini);
			exe_command(mini, mini->cmd_pipe[i]);
		}
		i++;
	}
	close_fd(mini);
	wait_processes(mini);
	// signal(SIGUSR2, process_on);
	// waiting(1000000);
	// mini->newline = 1;
}

int		exe_cd_exit(t_mini *mini)
{
	if (mini->cmd_pipe[0])
	{
		mini->options = cmd_split(mini, mini->cmd_pipe[0], ' ');
		if (ft_strncmp(mini->options[0], "exit", 4) == 0
			&& ft_strlen(mini->options[0]) == 4)
			built_exit(mini);
		if (ft_strncmp(mini->options[0], "cd", 2) == 0
			&& ft_strlen(mini->options[0]) == 2)
		{
			built_cd(mini);
			free_split(mini->options);
			return (1);
		}
		if (ft_strncmp(mini->options[0], "unset", 5) == 0
			&& ft_strlen(mini->options[0]) == 5)
		{
			built_unset(mini);
			free_split(mini->options);
			return (1);
		}
		if (ft_strncmp(mini->options[0], "export", 6) == 0
			&& ft_strlen(mini->options[0]) == 6)
		{
			built_export(mini);
			free_split(mini->options);
			return (1);
		}
		free_split(mini->options);
	}
	return (0);
}

void	pipex(t_mini *mini)
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
	signal(SIGUSR2, SIG_IGN);
	mini->newline = 0;
	if (exe_cd_exit(mini) == 0)
		exe_pipex(mini);
	signal(SIGUSR2, process_on);
	waiting(1000000);
	mini->newline = 1;
	if (mini->outfile != NULL)
		close(mini->out_fd);
	if (mini->infile != NULL)
		close(mini->in_fd);
	free_split(mini->paths);
	free_split(mini->cmd_pipe);
	mini->in_fd = -2;
	mini->out_fd = -2;
}
