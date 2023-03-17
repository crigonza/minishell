/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/17 08:22:40 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_command(t_command **command)
{
	t_command	*tmp;

	while ((*command) != NULL)
	{
		tmp = (*command);
		(*command) = (*command)->next;
		free(tmp->command);
		free(tmp);
	}
}

t_command	*last_command(t_command *command)
{
	while (command->next != NULL)
		command = command->next;
	return (command);
}

void	add_command(t_command **command, t_command *new_command)
{
	t_command	*tmp;
	int i = 0;

	while(new_command->command[i])
	{
		printf("%s|||", new_command->command[i]);
		i++;
	}
	printf("\n");
	tmp = *command;
	if (*command == NULL)
		*command = new_command;
	else
	{
		tmp = last_command(*command);
		tmp->next = new_command;
	}
}

t_command	*new_command(char **command)
{
	t_command	*new;
	int i = 0;

	new = malloc(sizeof(t_command));
	new->command = command;
	new->next = NULL;
	new->in = 0;
	new->out = 0;
	while(command[i])
	{
		printf("%s----", command[i]);
		i++;
	}
	printf("\n");
	return (new);
}

int	get_count(t_lexer **lexer)
{
	t_lexer	*tmp;
	int count;

	count = 0;
	tmp = *lexer;
	while (tmp != NULL && tmp->token_type != PIPE)
	{
		tmp = tmp->next;
		count++;
	}
	return(count - 1);
}

void	parser(t_lexer **lexer, t_list **envp)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command = NULL;
	parse_command(&command, lexer);
	print_command(&command);
	is_builtin(&command, envp);
	free_command(&command);
}

void parse_command(t_command **command, t_lexer **lexer)
{
	char    	**comm;
	t_lexer		*tmp;
    int    		i;

    i = 0;
	tmp = *lexer;
	comm = malloc(sizeof(char) * (get_count(lexer)));
	while (tmp != NULL && tmp->token_type != PIPE)
	{
		comm[i] = tmp->content;
		tmp = tmp->next;
        i++;
	}
	add_command(command, new_command(comm));
	if(tmp != NULL && tmp->token_type == PIPE)
	{
		tmp = tmp->next;
		parse_command(command, &tmp);
	}
}