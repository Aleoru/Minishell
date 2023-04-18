/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:49:54 by aoropeza          #+#    #+#             */
/*   Updated: 2023/04/14 17:50:02 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	in_quote(t_mini *mini, char *str, int i)
{
	mini->quote = 1;
	i++;
	while (mini->quote && str)
	{
		if (str[i] == '\'')
			mini->quote = 0;
		i++;
	}
	if (str[i] == '\0' && mini->quote)
	{
		write(2, "\033[31;1mError: Syntax Error\n\033[0m", 20);
		return (-1);
	}
	return (i);
}

char	*search_var(t_mini *mini, char *str, char *aux, int *i)
{
	int		start;
	char	*var;
	char	*tmp;

	*i += 1;
	start = *i;
	while (str[*i] != ' ' && str[*i] != '\"' && str[*i] != '\''
		&& str[*i] != '$' && str[*i] != '\0')
		*i += 1;
	var = ft_substr(str, start, *i - start);
/* 	printf("var: %s\n", expand_var(var, mini->env)); */
	if (ft_strnstr(var, "?", ft_strlen(var)))
		tmp = ft_strjoin(aux, ft_itoa(mini->p_exit));
	else
		tmp = ft_strjoin(aux, expand_var(var, mini->env));
	free(var);
	free(aux);
	return (tmp);
}

char	*in_double_quote(t_mini *mini, char *str, int i)
{
	int		j;
	char	*tmp;
	char	*aux;

	j = -1;
	mini->dquote = 1;
	aux = ft_calloc(1, ft_strlen(str));
	i++;
	while (++j < i)
		aux[j] = str[j];
	while (mini->dquote && str[j])
	{
		if (str[j] == '\"')
		{
			mini->dquote = 0;
			break ;
		}
		if (str[j] == '$')
		{
			aux = search_var(mini, str, aux, &j);
			while (aux[i])
				i++;
		}
		if (str[j] != '$')
			aux[i++] = str[j++];
	}
	tmp = ft_strjoin(aux, &str[j]);
/*  	printf("tmp: %s\n", tmp);	// borrar */
	return (tmp);
}
