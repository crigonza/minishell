/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:16:33 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/11 11:37:31 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process_sigquit(int pid)
{
	if (pid == 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(3, 2);
		ft_putchar_fd('\n', 2);
		g_exit_value = 131;
	}
}

void	process_signal(int signum, siginfo_t *info, void *context)
{		
	pid_t	pid;
	int		status;

	(void) context;
	(void) info;
	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGQUIT)
		process_sigquit(pid);
	else
	{
		if (pid == 0)
		{
			write(1, "\n", 1);
			g_exit_value = 130;
		}
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_exit_value = 1;
		}
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
	sigaction(SIGQUIT, &sa, NULL);
	signal(SIGTERM, SIG_IGN);
}
