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

	*i += 1;
	start = *i;
	while (!ft_strchr("<|> \0", mini->input[*i]))
		*i += 1;
	var = ft_substr(mini->input, start, *i - start);
/* 	printf("var:%s\n", var); */
	if (ft_strnstr(var, "?", ft_strlen(var)))
		tmp = ft_strjoin(str, ft_itoa(mini->p_exit));
	else
		tmp = ft_strjoin(str, expand_var(var, mini->env));
/* 	printf("tmp:%s\n", tmp);	//borrar */
	free(var);
	return (tmp);
}

char	*is_var_or_quote(t_mini *mini, char *str, int *i, int *j)
{
	if (mini->input[*i] == '\'' || mini->input[*i] == '\"')
	{
		if (mini->input[*i] == '\"')
			replace_var(mini, *i);
		str = not_del_spaces(mini, str, i, j);
	}
	if (mini->input[*i] == '$')
	{
		str = has_var(mini, str, i);
		while (str[*j])
			*j += 1;
	}
	return (str);
}

int	valid_var_syntax(char *str, int *i, int start)
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
/* 	if (declare == 1)
		printf("\"%s\" es declaración\n", ft_substr(str, start, end - start));
	else if (declare == 0)
		printf("\"%s\" es comando\n", ft_substr(str, start, end - start)); */
	return (declare);
}

void	var_syntax(t_mini *mini, char *str)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (str[i] != '\0')
	{
		if (str[i + 1] == ' ' || str[i + 1] == '\0')
		{
			end = i + 1;
			enter_var(mini, ft_substr(str, start, end - start));
			/* printf("var:%s\n", ft_substr(str, start, end - start)); */
			start = end + 1;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	mini->declare = 1;
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
			declare = valid_var_syntax(str, &i, start);
			start = i + 1;
			if (declare == 0)
				return ;
			declare = 0;
		}
		if (str[i] == '\0')
			break ;
	}
	printf("La input entera es declaración\n");
	var_syntax(mini, str);
}
