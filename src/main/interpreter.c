/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:11:18 by aoropeza          #+#    #+#             */
/*   Updated: 2023/03/28 17:11:19 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	split_cmd_line(t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	mini->cmd_pipe = ft_calloc(mini->n_cmd + 1, sizeof(char *));
/* 	del_spaces(mini); */
	str = del_sep_space(mini);
/* 	printf("str:%s\n", str);	//borrar */
	i = has_infile(mini, str);
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '|' && str[i + 1] != '|') || j < mini->n_cmd)
			i = is_cmd(mini, str, i, j++);
		if (str[i] == '$')
			i = has_var(mini, str, i, j - 1);
		if (str[i] == '>')
			i = has_outfile(mini, str, i);
		if (i == -1)
		{
			mini->error = -1;
			return ;
		}
		if (str[i] == '\0')
			break ;
	}
	printf("%d:%s\n", j - 1, mini->cmd_pipe[j - 1]);	//borrar
	mini->cmd_pipe[j] = NULL;
}

void	interpreter(t_mini *mini)
{
	int	i;

	i = 0;
	mini->n_cmd = 0;
	mini->n_out = 0;
	mini->append = 0;
	mini->heredoc = 0;
	mini->infile = NULL;
	mini->outfile = NULL;
	while (mini->input[i])
	{
		if (mini->input[i] == '|')
			mini->n_cmd++;
		if (mini->input[i] == '>' && mini->input[i + 1] != '>')
			mini->n_out++;
		if (mini->input[i] == '>' && mini->input[i + 1] == '>')
			mini->append++;
		i++;
	}
	mini->n_cmd++;
	/* printf("Nº cmd: %d\n", mini->n_cmd);	//borrar */
	split_cmd_line(mini);
	if (mini->error == -1)
		return ;
/* 	mini->fd = ft_calloc(mini->n_cmd, 2 * sizeof(int));
	mini->pid = malloc(mini->n_cmd * sizeof(pid_t)); */
	pipex(mini);
}
