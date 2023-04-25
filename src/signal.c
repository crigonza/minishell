/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:57:49 by itorres-          #+#    #+#             */
/*   Updated: 2023/04/25 12:26:54 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process_signal(int signum, siginfo_t *info, void *context)
{		
		(void)	signum;
		(void)	context;
		(void)	info;

		pid_t	pid;
		int		status;

		pid = waitpid(-1, &status, WNOHANG);
		if (pid == 0)
			write(1, "\n", 1);
		else 
		{
			write(1, "\n", 1);
			rl_on_new_line(); // LLama al prompt en una nueva linea
			rl_replace_line("", 0);  //limpia el texto previo
	    	rl_redisplay(); // Cambia el contenido por el que tenga el buffer
			
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
	signal(SIGTERM, SIG_IGN); /* Cambiamos la forma de trabajar de Control + D */
	signal(SIGQUIT, SIG_IGN);      /* Ignora Control + / */
}