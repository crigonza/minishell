/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:34 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/09 12:34:38 by crigonza         ###   ########.fr       */
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
	t_command	*tmp;
	int			i;
    
	tmp = *command;
	while (tmp != NULL)
	{
		while (tmp->command[i])
		{
			printf("%s, ", tmp->command[i]);
			i++;
		}
		tmp = tmp->next;
	}
	printf("\n");
}