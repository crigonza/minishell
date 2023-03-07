/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:34 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/07 11:58:18 by crigonza         ###   ########.fr       */
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
		printf("COMMAND: %s\nPATH: %s\nSTRING: %s\nIN:  %d\nOUT: %d\n", tmp->command, tmp->path, tmp->string, tmp->in, tmp->out);
		tmp = tmp->next;
	}
}