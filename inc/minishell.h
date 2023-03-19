/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:52:27 by aoropeza          #+#    #+#             */
/*   Updated: 2023/02/13 18:52:28 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ERROR_CMD "Command not found\n"

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

/* Necesarias para usar readline */
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <sys/types.h>
# include <sys/uio.h>

/* open, unlink */
# include <fcntl.h>

/* strerror */
# include <string.h>

# include "../libft/inc/libft.h"

typedef struct s_mini
{
	char	*input;
	char	**cmd_pipe;
	char	**paths;
	char	*cmd;
	char	**options;
	int		fd[10][2];
	pid_t	pid[10];
	int		n_cmd;
	char	*infile;
	char	*outfile;
	int		in_fd;
	int		out_fd;
	int		double_out;
}	t_mini;

/*
**	EXEC
*/
void	get_env_paths(t_mini *mini, char **envp);
void	exec_cmd(t_mini mini, char *str, char **envp);
void	interpreter(t_mini *mini, char **envp);
void 	pipex(t_mini *mini, char **envp);

#endif
