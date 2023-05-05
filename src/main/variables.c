/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:18:34 by aoropeza          #+#    #+#             */
/*   Updated: 2023/04/19 12:18:36 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*has_var(t_mini *mini, char *str, int *i)
{
	int		start;
	char	*var;
	char	*tmp;
	char	*expand;

	*i += 1;
	start = *i;
	if (mini->input[*i] == '?')
	{
		*i += 1;
		var = ft_itoa(mini->p_exit);
		tmp = ft_strjoin(str, var);
		return (free(str), free(var), tmp);
	}
	while (mini->input[*i] != '$' && ft_isalnum(mini->input[*i])
		&& mini->input[*i] != '\0')
		*i += 1;
	var = ft_substr(mini->input, start, *i - start);
	expand = expand_var_all(mini, var);
	if (expand)
		tmp = ft_strjoin(str, expand);
	else
		tmp = ft_strdup(str);
	return (free(str), free(var), free(expand), tmp);
}

char	*is_var_or_quote(t_mini *mini, char *str, int *i, int *j)
{
	if (mini->input[*i] == '\'' || mini->input[*i] == '\"')
		str = not_del_spaces(mini, str, i, j);
	if (mini->input[*i] == '$')
	{
		str = has_var(mini, str, i);
		while (str[*j])
			*j += 1;
	}
	return (str);
}

int	valid_var_syntax(t_mini *mini, char *str, int *i, int start)
{
	int	declare;
	int	end;

	declare = 0;
	end = *i + 1;
	*i = start;
	while (*i < end)
	{
		if (str[*i] == '=')
			declare = 1;
		*i += 1;
	}
	mini->declare = declare;
	return (declare);
}

void	var_syntax(t_mini *mini, char *str)
{
	int		i;
	int		start;
	int		end;
	char	*var;

	i = 0;
	start = 0;
	end = 0;
	while (str[i] != '\0')
	{
		if (str[i + 1] == ' ' || str[i + 1] == '\0')
		{
			end = i + 1;
			var = ft_substr(str, start, end - start);
			enter_var(mini, var);
			start = end + 1;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	mini->declare = 1;
	free(var);
}

void	can_declare_var(t_mini *mini, char *str)
{
	int	i;
	int	declare;
	int	start;

	i = -1;
	declare = 0;
	start = 0;
	while (str[++i] != '\0')
	{
		if (str[i + 1] == ' ' || str[i + 1] == '\0')
		{
			if (!ft_isalpha(str[start]))
				return ;
			declare = valid_var_syntax(mini, str, &i, start);
			start = i + 1;
			if (declare == 0)
				return ;
			declare = 0;
		}
		if (str[i] == '\0')
			break ;
	}
	var_syntax(mini, str);
	mini->declare = 1;
}
