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

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	cwd[PATH_MAX];

	if (argc > 0 && argv[0])
	{
		ft_bzero(&mini, sizeof(t_mini));
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("Current dir: %s\n", cwd);
		while (1)
		{
			mini.input = readline("MiniHell> ");
			if (ft_strlen(mini.input) == 4)
				if (ft_memcmp("exit", mini.input, ft_strlen(mini.input)) == 0)
					exit(EXIT_SUCCESS);
			add_history(mini.input);
			get_env_paths(&mini, envp);
			interpreter(&mini, envp);
		}
	}
	return (0);
}

/* para compilar readline: -lreadline */
/* readline: lee la linea */
/* add_history: almacena la linea */
/* getcwd: ruta absoluta actual */
