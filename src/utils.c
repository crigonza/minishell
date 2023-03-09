/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:34 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/08 23:50:40 by crigonza         ###   ########.fr       */
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
	printf("*******************************\n");
}

void	print_command(t_command **command)
{
	t_command *tmp;
    
	tmp = *command;
	while (tmp != NULL)
	{
		tmp = tmp->next;
	}
}