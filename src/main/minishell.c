/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:52:12 by aoropeza          #+#    #+#             */
/*   Updated: 2023/02/13 18:52:15 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_void(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	atexit(ft_void);
	set_signals();
	if (argc > 0 && argv[0])
	{
		ft_bzero(&mini, sizeof(t_mini));
		mini.p_exit = 0;
		mini.newline = 1;
		init_env(&mini, envp);
		while (1)
		{
			if (mini.newline == 1)
			{
				mini.input = readline("\033[33;1mMiniHell> \033[0m");
				if (mini.input == NULL)
					return (free_mini(&mini), 0);
				if (ft_strlen(mini.input) != 0)
				{
					add_history(mini.input);
					get_env_paths(&mini);
					interpreter(&mini);
					free_split(mini.paths);
				}
				free(mini.input);
			}
		}
	}
	return (0);
}

/* para compilar readline: -lreadline */
/* readline: lee la linea */
/* add_history: almacena la linea */
/* getcwd: ruta absoluta actual */
