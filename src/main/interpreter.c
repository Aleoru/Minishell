/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:11:18 by aoropeza          #+#    #+#             */
/*   Updated: 2023/03/28 17:11:19 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_mini(t_mini *mini)
{
	mini->n_cmd = 0;
	mini->n_out = 0;
	mini->append = 0;
	mini->heredoc = 0;
	mini->declare = 0;
	mini->infile = NULL;
	mini->outfile = NULL;
	mini->quote = 0;
	mini->dquote = 0;
	mini->error = 0;
}

int	syntax_validation(t_mini *mini)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (mini->input[i])
	{
		if (ft_strchr("<|>", mini->input[i]))
			check++;
		if (ft_isalnum(mini->input[i]))
			check = 0;
		if (check > 2)
			return (-1);
		i++;
	}
	if (check > 2)
		return (-1);
	return (0);
}

int	split_cmd_line(t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	str = del_sep_space(mini);
/* 	printf("str:%s\n", str);	//borrar */
	if (mini->error == -1)
		return (free(str), -1);
	can_declare_var(mini, str);
	if (mini->declare == 1)
		mini->n_cmd = 0;
	mini->cmd_pipe = ft_calloc(mini->n_cmd + 1, sizeof(char *));
	i = has_infile(mini, str);
	j = 0;
	while (str[i] != '\0' && mini->declare == 0)
	{
		if ((str[i] == '|' && str[i + 1] != '|') || j < mini->n_cmd)
			i = is_cmd(mini, str, i, j++);
		if (str[i] == '>')
			i = has_outfile(mini, str, i);
		if (i == -1)
			return (free(str), -1);
		if (str[i] == '\0')
			break ;
	}
	mini->cmd_pipe[j] = NULL;
	return (free(str), 0);
}

void	interpreter(t_mini *mini)
{
	int	i;

	i = 0;
	init_mini(mini);
	if (syntax_validation(mini) == -1)
	{
		write(2, ERROR_SYN, ft_strlen(ERROR_SYN));
		mini->p_exit = 2;
		return ;
	}
	while (mini->input[i])
	{
		if (mini->input[i] == '|')
			mini->n_cmd++;
		if (mini->input[i] == '>' && mini->input[i + 1] != '>')
			mini->n_out++;
		if (mini->input[i] == '>' && mini->input[i + 1] == '>')
			mini->append++;
		i++;
	}
	mini->n_cmd++;
	if (split_cmd_line(mini) == -1)
	{
		write(2, ERROR_SYN, ft_strlen(ERROR_SYN));
		mini->p_exit = 2;
		return ;
	}
/* 	mini->fd = ft_calloc(mini->n_cmd, 2 * sizeof(int));
	mini->pid = malloc(mini->n_cmd * sizeof(pid_t)); */
	if (mini->n_cmd > 0)
		pipex(mini);
}
