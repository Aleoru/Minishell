/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:09:49 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/05/01 17:09:52 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

void	free_mini(t_mini *mini)
{
	free_split(mini->env);
	free_split(mini->var);
	free(mini->input);
	rl_clear_history();
}

void	free_son(t_mini *mini)
{
	free_split(mini->options);
	if (mini->declare == 0)
		free_split(mini->cmd_pipe);
	free_split(mini->env);
	free_split(mini->var);
	free(mini->input);
	if (mini->infile != NULL)
		free(mini->infile);
	if (mini->outfile != NULL)
		free(mini->outfile);
	if (mini->limit != NULL)
		free(mini->limit);
}
