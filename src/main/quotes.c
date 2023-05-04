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
		mini->error = -1;
		return (-1);
	}
	return (i);
}

/* char	*search_var(t_mini *mini, char *str, char *aux, int *i)
{
	int		start;
	char	*var;
	char	*tmp;
	char	*expand;

	*i += 1;
	start = *i;
	if (str[*i] == '?')
	{
		*i += 1;
		var = ft_itoa(mini->p_exit);
		tmp = ft_strjoin(aux, var);
		return (free(aux), free(var), tmp);
	}
	while (ft_isalnum(str[*i]) && str[*i] != '\0')
		*i += 1;
	var = ft_substr(str, start, *i - start);
	expand = expand_var_all(mini, var);
	if (expand)
		tmp = ft_strjoin(aux, expand);
	else
		tmp = ft_strdup(aux);
	free(var);
	free(aux);
	return (free(expand), tmp);
}

int	final_quote(t_mini *mini, char *str, int j)
{
	if (str[j] == '\"')
	{
		mini->dquote = 0;
		return (1);
	}
	return (0);
}

char	*in_double_quote(t_mini *mini, char *str, int i)
{
	int		j;
	char	*tmp;
	char	*aux;

	j = -1;
	aux = ft_calloc(1, ft_strlen(str));
	i++;
	while (++j < i)
		aux[j] = str[j];
	while (mini->dquote && str[j])
	{
		if (final_quote(mini, str, j))
			break ;
		if (str[j] == '$')
		{
			aux = search_var(mini, str, aux, &j);
			while (aux[i])
				i++;
		}
		if (str[j] != '$' && str[j] != '\"')
			aux[i++] = str[j++];
	}
	tmp = ft_strjoin(aux, &str[j]);
	return (free(aux), tmp);
} */
