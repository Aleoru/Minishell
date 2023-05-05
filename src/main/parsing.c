/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:16:31 by aoropeza          #+#    #+#             */
/*   Updated: 2023/04/14 18:16:33 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_heredoc(t_mini *mini, char *str, int i)
{
	int	start;

	i++;
	if (str[i + 1] == ' ')
		i += 1;
	i++;
	start = i;
	while (!ft_strchr("<|> ", str[i]) && str[i] != '\0')
		i++;
	mini->limit = ft_substr(str, start, i - start);
	mini->heredoc = 1;
	return (i);
}

int	has_infile(t_mini *mini, char *str)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (str[i] == '<' && str[i + 1] != '<')
	{
		if (str[i + 1] == ' ')
			i += 1;
		i++;
		start = i;
		while (!ft_strchr("<|> ", str[i]) && str[i] != '\0')
			i++;
		mini->infile = ft_substr(str, start, i - start);
		return (i + 1);
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		i = has_heredoc(mini, str, i);
		return (i + 1);
	}
	return (mini->infile = NULL, 0);
}

int	has_outfile(t_mini *mini, char *str, int i)
{
	int		start;
	char	*outfile;

	start = 0;
	if ((str[i] == '>' && str[i + 1] != '>')
		|| (str[i] == '>' && str[i + 1] == '>'))
	{
		if (str[i + 1] == '>')
			i += 1;
		if (str[i + 1] == ' ')
			i += 1;
		i++;
		start = i;
		while (!ft_strchr("<|> ", str[i]) && str[i] != '\0')
			i++;
		outfile = ft_substr(str, start, i - start);
		mini->outfile = ft_strjoin("./", outfile);
		free(outfile);
		return (i);
	}
	return (mini->outfile = NULL, 0);
}

int	is_cmd(t_mini *mini, char *str, int i, int j)
{
	int	start;

	if (str[i + 1] == ' ')
		i += 1;
	if (str[i] == '|')
		i++;
	start = i;
	while (str[i] != '|' && str[i] != '>' && str[i] != '$'
		&& str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = in_quote(mini, str, i);
		if (i == -1)
			return (-1);
		i++;
	}
	mini->cmd_pipe[j] = ft_substr(str, start, i - start);
	return (i);
}
