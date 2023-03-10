/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:26:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/09 18:55:04 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void is_builtin(t_command **command)
{
    char *com;

    com = (*command)->command[0];
    if(!ft_strncmp("/bin/echo", com, ft_strlen(com)))
        echo((*command)->command);
    else
        executer((*command)->command, (*command)->envp);

}


void echo(char **command)
{
    ft_putstr_fd(command[1], 1);
    write(1,"\n",1);
}