/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 21:46:19 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char	**comm;
	t_lexer	*tmp;
	int		i;
	int		pipe;
	int		redir;

	i = 0;
	pipe = 0;
	redir = 0;
	tmp = *lexer;
	comm = malloc(sizeof(char *) * (get_count(lexer) + 1));
	comm[get_count(lexer)] = NULL;
	while (tmp != NULL && tmp->token_type != PIPE && redir != 2)
	{
		if (redir == 1)
			redir ++;
		if(tmp->token_type == D_LESS_THAN)
			redir = 1;
		comm[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	if (tmp != NULL && tmp->token_type == PIPE)
		pipe = 1;
	add_command(command, new_command(comm, pipe));
	if (tmp != NULL && (tmp->token_type == PIPE || redir == 2))
	{
		if(redir != 2)
			tmp = tmp->next;
		parse_command(command, &tmp);
	}
}

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

void	add_command(t_full_comm **command, t_full_comm *new_command)
{
	t_full_comm	*tmp;

	tmp = *command;
	if (*command == NULL)
		*command = new_command;
	else
	{
		while(tmp->next != NULL)
			tmp = tmp->next;
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
