/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:19:09 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/04/14 18:19:12 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	set_env_pwd(t_mini *mini, char *var_name)
{
	char	*pwd;
	char	*name;
	char	*buff;

	buff = malloc(sizeof(char) * 1000);
	getcwd(buff, 1000);
	pwd = ft_strjoin(var_name, buff);
	enter_var(mini, pwd);
	name = name_var(pwd);
	export(mini, name);
	free(pwd);
	free(name);
	free(buff);
}

int	built_cd(t_mini *mini)
{
	int	returned;

	if (get_argc(mini) == 2)
	{
		set_env_pwd(mini, "OLDPWD=");
		returned = chdir(mini->options[1]);
		if (returned != 0)
		{
			mini->p_exit = 1;
			perror("error");
		}
		set_env_pwd(mini, "PWD=");
	}
	else if (get_argc(mini) > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		mini->p_exit = 1;
	}
	return (0);
}
