/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:20:41 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/04/14 18:20:43 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_echo(t_mini *mini)
{
	int	i;
	int	jump;

	i = 1;
	jump = 1;
	while (mini->options[i] && ft_strncmp(mini->options[i], "-n", 2) == 0)
	{
		jump = 0;
		i++;
	}
	while (mini->options[i])
	{
		printf("%s ", mini->options[i]);
		i++;
	}
	if (jump == 1)
		printf("\n");
	free_son(mini);
	exit(0);
}
