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
	char	*input;
	char	cwd[PATH_MAX];

	if (argc > 0 && argv[0])
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("Current dir: %s\n", cwd);
		while (1)
		{
			input = readline("MiniHell> ");
			if (ft_strlen(input) == 4)
				if (ft_memcmp("exit", input, 4) == 0)
					exit(EXIT_SUCCESS);
			add_history(input);
			get_env_paths(&mini, envp);
			if (fork() != 0)
				wait(NULL);
			else
				exec_cmd(mini, input, envp);
		}
	}
	return (0);
}

/* para compilar readline: -lreadline */
/* readline: lee la linea */
/* add_history: almacena la linea */
/* getcwd: ruta absoluta actual */
