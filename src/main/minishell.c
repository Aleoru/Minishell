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

/* void	ft_void(void)
{
	system("leaks -q minishell");
} */

static int	input(t_mini *mini)
{
	while (1)
	{
		if (mini->newline == 1)
		{
			mini->input = readline("\033[33;1mMinishell> \033[0m");
			if (mini->input == NULL)
			{
				free_split(mini->env);
				free_split(mini->var);
				free(mini->input);
				rl_clear_history();
				return (0);
			}
			if (ft_strlen(mini->input) != 0 && is_blank(mini) == 1)
			{
				add_history(mini->input);
				interpreter(mini);
			}
			free(mini->input);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	if (argc == 1 && argv[0])
	{
		set_signals();
		ft_bzero(&mini, sizeof(t_mini));
		mini.p_exit = 0;
		mini.newline = 1;
		init_env(&mini, envp);
		input(&mini);
	}
	else
	{
		write(2, "error: too many arguments\n", 26);
		return (127);
	}
	return (0);
}
