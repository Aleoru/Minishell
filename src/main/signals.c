/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:22:06 by aoropeza          #+#    #+#             */
/*   Updated: 2023/04/25 17:22:08 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_on(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	control_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	kill(0, SIGUSR2);
}

void	set_signals(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR2, process_on);
}
