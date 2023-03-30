/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:57:49 by itorres-          #+#    #+#             */
/*   Updated: 2023/03/30 14:57:51 by itorres-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/minishell.h"

void	process_signal(int signum)
{
	if (signum == SIGINT)
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

	sa.sa_handler = &process_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);  /* Cambiamos la forma de trabajar de Control + C */
	sigaction(SIGTERM, &sa, NULL);  /* Cambiamos la forma de trabajar de Control + D */
	signal(SIGQUIT, SIG_IGN);      /* Ignora Control + / */
}