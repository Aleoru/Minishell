/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:45:50 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/04/14 18:45:53 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_pwd(t_mini *mini)
{
	char	cwd[1000];

	if (get_argc(mini) == 1)
	{
		getcwd(cwd, 1000);
		printf("%s\n", cwd);
	}
	else
	{
		write(2, "pwd: to many arguments", 23);
		return (2);
	}
	free_son(mini);
	exit(0);
}
