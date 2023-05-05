/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:58 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_command(t_full_comm **command)
{
	t_full_comm	*tmp;

	while ((*command) != NULL)
	{
		tmp = (*command);
		(*command) = (*command)->next;
		free(tmp->command);
		free(tmp);
	}
}

t_full_comm	*last_command(t_full_comm *command)
{
	while (command->next != NULL)
		command = command->next;
	return (command);
}

void	add_command(t_full_comm **command, t_full_comm *new_command)
{
	t_full_comm	*tmp;

	tmp = *command;
	if (*command == NULL)
		*command = new_command;
	else
	{
		tmp = last_command(*command);
		tmp->next = new_command;
	}
}

t_full_comm	*new_command(char **command, int pipe)
{
	t_full_comm	*new;

	new = malloc(sizeof(t_full_comm));
	new->command = command;
	new->next = NULL;
	new->pipe_next = pipe;
	new->filein = NULL;
	new->fileout = NULL;
	new->fdin = 0;
	new->fdout = 1;
	return (new);
}
