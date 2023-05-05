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
	if (str[i] == '\'')
		mini->quote = 1;
	else if (str[i] == '\"')
		mini->dquote = 1;
	i++;
	while ((mini->quote || mini->dquote) && str[i] != '\0')
	{
		if (str[i] == '\'')
			mini->quote = 0;
		else if (str[i] == '\"')
			mini->dquote = 0;
		i++;
	}
	if (mini->quote || mini->dquote)
		mini->error = -1;
	return (i);
}
