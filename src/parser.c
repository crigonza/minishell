/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/14 20:14:01 by crigonza         ###   ########.fr       */
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
	return(count);

}

void	parser(t_lexer **lexer, t_list **envp)
{
	t_lexer		*tmp;
	t_command	*command;
	char    	**comm;
    int    		i;
	int			j;

	j = 0;
    i = 0;
	tmp = *lexer;
	command = malloc(sizeof(t_command));
	command = NULL;
	comm = malloc(sizeof(char*) * get_count(lexer) + 1);
	while (tmp != NULL && tmp->token_type != PIPE)
	{
		//if (tmp->token_type == COMMAND  || tmp->token_type == PATH || tmp->token_type == STRING)
		comm[i] = tmp->content; 
		tmp = tmp->next;
        i++;
	}
	comm[i] = NULL;
	add_command(&command, new_command(comm));
	print_command(&command);
	is_builtin(&command, envp);
}