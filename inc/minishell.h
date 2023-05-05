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
# define ERROR_CMD "Command not found: "
# define ERROR_SYN "Syntax error\n"

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

/* signal */
# include <signal.h>

# include "../libft/inc/libft.h"

typedef struct s_mini
{
	int		error;
	char	*input;
	char	**cmd_pipe;
	char	**paths;
	char	*cmd;
	char	**options;
	int		fd[10][2];
	pid_t	pid[10];
	int		n_cmd;
	int		n_out;
	char	*infile;
	char	*outfile;
	int		in_fd;
	int		out_fd;
	int		append;
	char	*limit;
	int		heredoc;
	int		quote;
	int		dquote;
	char	**env;
	char	**var;
	int		env_len;
	int		var_len;
	int		p_exit;
	int		declare;
	int		newline;
}	t_mini;

/*
**	EXEC
*/
void	get_env_paths(t_mini *mini);
void	exec_cmd(t_mini mini, char *str);
void	interpreter(t_mini *mini);

/* pipex */
void	seting_pipex(t_mini *mini);
void	pipex(t_mini *mini);
void	exe_pipex(t_mini *mini);
void	exe_command(t_mini *mini, char *cmd);
int		exe_alone_builtin(t_mini *mini);
char	*get_cmd(char **paths, char *cmd);

/*
**	ENV
*/

/* exporta una variable de var a env */
int		export(t_mini *mini, char *var_name);

/* Recive el nombre de una variable y devuelve su contenido */
char	*expand_var(char *name_var, char **env);
char	*expand_var_all(t_mini *mini, char *name_var);

/* Añade una variable a var */
void	enter_var(t_mini *mini, char *enter_var);

/* Devuelve el nombre de la variable dentro de una cadena */
char	*name_var(char *env_var);

/* Crea una copia de **envp original para iniciar env y var */
void	init_env(t_mini *mini, char **envp);

/* Añade un nuevo char *str a un char **src */
char	**add_str(char **src, char *str, int *len);

/* Comprueba que la variable existe en la posicion i del char **src */
int		contain_var(char **src, char *env_var, int i);

/* Borra un char *var_name de un char **src */
char	**del_var(char **src, char *var_name, int len);

/* Busca en el char **src una variable con el mismo nombre que
char *new_value y cambia el contenido */
void	change_value(char **src, char *new_value);

/* Retorna el numero de argumenos en mini->options */
int		get_argc(t_mini *mini);

/* Acualiza la variable SHLVL */
void	shell_level(t_mini *mini);

/* Imprime las variables de env y var. SOLO DEBUG */
void	print_env(t_mini *mini);

/*
*	INTERPRETER
*/

int		in_quote(t_mini *mini, char *str, int i);
//char	*in_double_quote(t_mini *mini, char *str, int i);
int		has_heredoc(t_mini *mini, char *str, int i);
int		has_infile(t_mini *mini, char *str);
int		has_outfile(t_mini *mini, char *str, int i);
int		is_cmd(t_mini *mini, char *str, int i, int j);
char	*del_sep_space(t_mini *mini);
char	*is_var_or_quote(t_mini *mini, char *str, int *i, int *j);
void	replace_var(t_mini *mini);
char	*not_del_spaces(t_mini *mini, char *str, int *i, int *j);
void	can_declare_var(t_mini *mini, char *str);
char	*has_var(t_mini *mini, char *str, int *i);

/*
*	BUILT-INS
*/
/* Built-in env sin opciones */
int		built_env(t_mini *mini);

/* Built-in con ruta relativa o absuluta */
int		built_cd(t_mini *mini);

/* Built-in export sin opciones */
int		built_export(t_mini *mini);

/* Built-in unset sin opciones */
int		built_unset(t_mini *mini);

/* Built-in echo con opcion -n */
int		built_echo(t_mini *mini);

/* Built-in exit con valor de terminación */
int		built_exit(t_mini *mini);

/* Built-in pwd sin opciones*/
int		built_pwd(t_mini *mini);

/* signals */
void	set_signals(void);
void	process_on(int signal);
void	control_c(int sig);

/*
*	UTILS
*/

void	free_split(char **split);
void	free_mini(t_mini *mini);
void	free_son(t_mini *mini);
int		split_len(char **split);
char	**cpy_split(char **split);
char	**cmd_split(t_mini *mini, char *str, char c);
void	sort_strings(char **split);
int		is_blank(t_mini *mini);

#endif
