/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:28:34 by aoropeza          #+#    #+#             */
/*   Updated: 2023/04/14 20:28:37 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	replace_var(t_mini *mini, int i)
{
	char	*tmp;

	tmp = in_double_quote(mini, mini->input, i);
	free(mini->input);
	mini->input = tmp;
 	/* printf("input: %s\n", mini->input);		//borrar */
}

char	*not_del_spaces(t_mini *mini, char *str, int *i, int *j)
{
	if (mini->input[*i] == '\'')
		mini->quote = 1;
	else if (mini->input[*i] == '\"')
		mini->dquote = 1;
	str[*j] = mini->input[*i];
	*i += 1;
	*j += 1;
	while (mini->quote || mini->dquote)
	{
		if (mini->input[*i] == '\'')
			mini->quote = 0;
		else if (mini->input[*i] == '\"')
			mini->dquote = 0;
		str[*j] = mini->input[*i];
		*j += 1;
		*i += 1;
	}
	return (str);
}

void	del_spaces(t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = ft_calloc(1, ft_strlen(mini->input) * sizeof(char));
	while (mini->input[i])
	{
		while (mini->input[i] == ' ' && mini->input[i] != '\0')
			i++;
		while (mini->input[i] != ' ' && mini->input[i] != '\0')
		{
			if (mini->input[i] == '\'' || mini->input[i] == '\"')
			{
				if (mini->input[i] == '\"')
					replace_var(mini, i);
				str = not_del_spaces(mini, str, &i, &j);
			}
			str[j++] = mini->input[i++];
			if (mini->input[i] == ' ')
				str[j++] = mini->input[i++];
		}
	}
	if (str[j - 1] == ' ')
		str[j - 1] = '\0';
	else
		str[j] = '\0';
	free(mini->input);
	mini->input = str;
}

char	*deleting_spaces(t_mini *mini, char *str, int *i, int *j)
{
	if (ft_strchr("<|>", mini->input[*i]) && mini->input[*i - 1] == ' ')
	{
		str[*j - 1] = mini->input[*i];
		if (mini->input[*i + 1] == ' ')
			*i += 1;
		*i += 1;
	}
	else if (ft_strchr("<|>", mini->input[*i]) && mini->input[*i + 1] == ' ')
	{
		str[*j++] = mini->input[*i];
		*i += 2;
	}
	return (str);
}

char	*del_sep_space(t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	del_spaces(mini);
	str = ft_calloc(1, ft_strlen(mini->input) * sizeof(char));
	/* printf("input:%s\n", mini->input);	// borrar */
	while (mini->input[i])
	{
		if (mini->input[i] == '\'' || mini->input[i] == '\"')
			str = not_del_spaces(mini, str, &i, &j);
		if (!mini->input[i])
			break ;
		if (ft_strchr("<|>", mini->input[i]))
			str = deleting_spaces(mini, str, &i, &j);
		str[j++] = mini->input[i++];
	}
	str[j] = '\0';
	return (str);
}