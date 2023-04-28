/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:23:04 by aoropeza          #+#    #+#             */
/*   Updated: 2023/04/07 13:23:07 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**split_free(char **array)
{
	size_t	elem;

	elem = 0;
	while (array)
	{
		free(array[elem]);
		elem++;
	}
	free (array);
	return (NULL);
}

static size_t	count_word(t_mini *mini, char *str, char c)
{
	size_t	index;
	size_t	elem;

	index = 0;
	elem = 0;
	while (str[index] == c)
		index++;
	while (str[index])
	{
		if (str[index] == '\'' && !mini->quote)
			mini->quote = 1;
		if (str[index] == '\'' && mini->quote)
			mini->quote = 0;
		if (!mini->quote && str[index] == c && str[index + 1] != c
			&& str[index + 1] != '\0')
			elem++;
		index++;
	}
	return (elem + 1);
}

char	*replace_by_spaces(t_mini *mini, char *str, size_t *i, size_t *start)
{
	if (mini->input[*i] == '\'')
		mini->quote = 1;
	else if (mini->input[*i] == '\"')
		mini->dquote = 1;
	str[*i] = ' ';
	*i += 1;
	*start = *i;
	while (mini->quote || mini->dquote)
	{
		if (mini->input[*i] == '\'')
			mini->quote = 0;
		else if (mini->input[*i] == '\"')
			mini->dquote = 0;
		*i += 1;
	}
	str[*i - 1] = ' ';
	return (str);
}

char	**cmd_split(t_mini *mini, char *str, char c)
{
	char	**array;
	size_t	elem;
	size_t	str_pos;
	size_t	start;

	if (str == NULL)
		return (NULL);
	array = malloc((count_word(mini, str, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	str_pos = 0;
	elem = 0;
	while (str[str_pos] && elem < count_word(mini, str, c))
	{
		while (str[str_pos] == c && str[str_pos] != '\0')
			str_pos++;
		start = str_pos;
		if (str[str_pos] == '\'' || str[str_pos] == '\"')
			str = replace_by_spaces(mini, str, &str_pos, &start);
		else
			while (str[str_pos] != c && str[str_pos] != '\0')
				str_pos++;
		array[elem++] = ft_substr(str, start, (str_pos - start));
		if (!array[elem - 1])
			return (split_free(array));
	}
	array[elem] = 0;
	return (array);
}

void	free_son(t_mini *mini)
{
	free_split(mini->options);
	free_split(mini->paths);
	free_split(mini->cmd_pipe);
	free_split(mini->env);
	free_split(mini->var);
	free(mini->input);
	if (mini->infile)
		free(mini->infile);
	if (mini->outfile)
		free(mini->outfile);
	if (mini->limit)
		free(mini->limit);
}
