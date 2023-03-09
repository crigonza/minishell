/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/07 21:07:31 by crigonza         ###   ########.fr       */
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

t_command	*new_command(char **command)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	new->command = command;
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
	char    **comm;
    int     i;

    i = 0;
	command = malloc(sizeof(t_command));
	command = NULL;
	while ((*lexer) != NULL && (*lexer)->token_type != PIPE)
	{
		if ((*lexer)->token_type == COMMAND)
			comm[i] = set_command((*lexer)->content);
		/* if ((*lexer)->token_type == SLASH || ((*lexer)->token_type == PATH))
		{
			printf("%s\n", (*lexer)->content);

			if (path == NULL)
				path = set_command((*lexer)->content);
			else
				path = ft_strjoin(path, (*lexer)->content);
		} */
		if ((*lexer)-> token_type == STRING)
		{
			comm[i] = set_command((*lexer)->content);
		}
		(*lexer) = (*lexer)->next;
        i++;
	}
    printf("%s\n", comm[i]);
	//add_command(&command, new_command(&comm));
	/* if ((*lexer)->token_type == PIPE)
	{
		(*lexer) = (*lexer)->next;
		parser(lexer);
	} */
	//print_command(&command);
}