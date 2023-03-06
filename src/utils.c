/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:34 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/06 21:20:11 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp != NULL)
	{
		printf("TOKEN %d = %s\n", tmp->token_type, tmp->content);
		tmp = tmp->next;
	}
}

void	print_command(t_command **command)
{
	t_command *tmp;
	int i;

	i = 0;
	tmp = *command;
	while (tmp != NULL)
	{
		printf("COMMAND: %s\nPATH: ", tmp->command);
		while (tmp->path[i])
		{
			printf("%s", tmp->path[i]);
			i++;
		}
		printf("\nIN:  %d\nOUT: %d\n", tmp->in, tmp->out);
		tmp = tmp->next;
	}
}