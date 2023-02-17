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
# define ERROR_CMD "Command not found"

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

/* Necesarias para usar readline */
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "../libft/inc/libft.h"

typedef struct mini
{
	char	**paths;
	char	*cmd;
	char	**options;
}	t_mini;

/*
**	EXEC
*/
void	get_env_paths(t_mini *mini, char **envp);
void	exec_cmd(t_mini mini, char *str, char **envp);

#endif
