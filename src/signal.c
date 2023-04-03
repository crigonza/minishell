/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:57:49 by itorres-          #+#    #+#             */
/*   Updated: 2023/04/03 09:35:29 by itorres-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/minishell.h"

void	process_signal(int signum)
{		
		(void) signum;
    
		write(1, "\n", 1);
		rl_on_new_line(); // LLama al prompt en una nueva linea
		rl_replace_line("", 0);  //limpia el texto previo
	    rl_redisplay(); // Cambia el contenido por el que tenga el buffer 
		
    
}

void	config_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, process_signal); /* Cambiamos la forma de trabajar de Control + C */
	signal(SIGTERM, SIG_IGN); /* Cambiamos la forma de trabajar de Control + D */
	signal(SIGQUIT, SIG_IGN);      /* Ignora Control + / */
}