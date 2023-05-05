/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:16:33 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/05 13:17:04 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process_signal(int signum, siginfo_t *info, void *context)
{		
	pid_t	pid;
	int		status;

	(void) signum;
	(void) context;
	(void) info;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == 0)
		write(1, "\n", 1);
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	config_signals(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = process_signal;
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
