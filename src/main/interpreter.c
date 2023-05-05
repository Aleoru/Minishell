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
	int	i;

	i = 0;
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
	while (mini->input[i])
	{
		if (mini->input[i] == '\'' || mini->input[i] == '\"')
			i = in_quote(mini, mini->input, i);
		if (mini->input[i] == '|')
			mini->n_cmd++;
		if (mini->input[i] == '>' && mini->input[i + 1] != '>')
			mini->n_out++;
		if (mini->input[i] == '>' && mini->input[i + 1] == '>')
			mini->append++;
		i++;
	}
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

int	parsing(t_mini *mini, char *str, int *i, int j)
{
	if ((str[*i] == '|' && str[*i + 1] != '|') || j < mini->n_cmd)
		*i = is_cmd(mini, str, *i, j++);
	if (str[*i] == '>')
		*i = has_outfile(mini, str, *i);
	return (j);
}

int	split_cmd_line(t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	str = del_sep_space(mini);
	if (mini->error == -1)
		return (free(str), -1);
	can_declare_var(mini, str);
	if (mini->declare == 1)
		mini->n_cmd = 0;
	else
		mini->cmd_pipe = ft_calloc(mini->n_cmd + 1, sizeof(char *));
	i = has_infile(mini, str);
	j = 0;
	while (str[i] != '\0' && mini->declare == 0)
	{
		j = parsing(mini, str, &i, j);
		if (i == -1)
			return (free(str), -1);
		if (str[i] == '\0' || j >= mini->n_cmd)
			break ;
	}
	if (mini->declare == 0)
		mini->cmd_pipe[j] = NULL;
	return (free(str), 0);
}

void	interpreter(t_mini *mini)
{
	init_mini(mini);
	mini->n_cmd++;
	if (syntax_validation(mini) == -1)
	{
		write(2, ERROR_SYN, ft_strlen(ERROR_SYN));
		mini->p_exit = 2;
		return ;
	}
	if (split_cmd_line(mini) == -1)
	{
		write(2, ERROR_SYN, ft_strlen(ERROR_SYN));
		mini->p_exit = 2;
		return ;
	}
	if (mini->n_cmd > 0)
		pipex(mini);
	if (mini->declare == 0)
		free_split(mini->cmd_pipe);
}
