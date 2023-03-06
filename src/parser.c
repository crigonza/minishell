/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/06 21:20:05 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_command	*last_command(t_command *command)
{
	while (command->next != NULL)
		command = command->next;
	return (command);
}

void	add_command(t_command **command, t_command *new_command)
{
	t_command	*tmp;

	tmp = *command;
	if (*command == NULL)
		*command = new_command;
	else
	{
		tmp = last_command(*command);
		tmp->next = new_command;
	}
}

t_command	*new_command(char *command, char **path)
{
	t_command	*new;

	new->command = command;
	new->path = path;
	new->next = NULL;
	new->in = 0;
	new->out = 0;
	return (new);
}

char	*set_command(char *command)
{
	char	*tmp;

	tmp = malloc(sizeof(ft_strlen(command) + 1));
	ft_strlcpy(tmp, command, ft_strlen(command) + 1);
	return (tmp);
}

void	parser(t_lexer **lexer)
{
	t_command *command;
	char *comm;
	char **path;
	int i;

	path = malloc(sizeof(path));
	command = malloc(sizeof(t_command));
	command = NULL;
	while ((*lexer) != NULL && (*lexer)->token_type != PIPE)
	{
		if ((*lexer)->token_type == COMMAND)
			comm = set_command((*lexer)->content);
		if (((*lexer)->token_type == SLASH
				&& (*lexer)->next->token_type == PATH)
			|| ((*lexer)->token_type == PATH))
		{
			i = 0;
			while ((*lexer)->token_type == SLASH
				|| (*lexer)->token_type == PATH)
			{
				path[i] = malloc(sizeof(ft_strlen((*lexer)->content) + 1));
				ft_strlcpy(path[i], (*lexer)->content,
						ft_strlen((*lexer)->content) + 1);
				(*lexer) = (*lexer)->next;
				i++;
			}
		}
		(*lexer) = (*lexer)->next;
	}
	add_command(&command, new_command(comm, path));
	print_command(&command);
}