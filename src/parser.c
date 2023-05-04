/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/04 09:43:39 by crigonza         ###   ########.fr       */
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

int	get_count(t_lexer **lexer)
{
	t_lexer	*tmp;
	int		count;

	count = 0;
	tmp = *lexer;
	while (tmp != NULL && tmp->token_type != PIPE)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

void	parser(t_lexer **lexer, t_ev **envp)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->command = NULL;
	command->env = envp;
	parse_command(&command->command, lexer);
	print_command(&command->command);
	exe_init(command);
	free_command(&command->command);
	free(command);
}

void	parse_command(t_full_comm **command, t_lexer **lexer)
{
	char **comm;
	t_lexer *tmp;
	int i;
	int pipe;

	i = 0;
	pipe = 0;
	tmp = *lexer;
	comm = malloc(sizeof(char *) * (get_count(lexer) + 1));
	comm[get_count(lexer)] = NULL;
	while (tmp != NULL && tmp->token_type != PIPE)
	{
		comm[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	if(tmp != NULL && tmp->token_type == PIPE)
		pipe = 1;
	add_command(command, new_command(comm, pipe));
	if (tmp != NULL && tmp->token_type == PIPE)
	{
		tmp = tmp->next;
		parse_command(command, &tmp);
	}
}