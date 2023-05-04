/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:34 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/04 12:19:39 by itorres-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

void	print_command(t_full_comm **command)
{
	t_full_comm	*tmp;
	int			i;

	i = 0;
	tmp = *command;
	while (tmp != NULL)
	{
		while (tmp->command[i] != NULL)
		{
			printf("%s, ", tmp->command[i]);
			i++;
		}
		printf("\n");
		i = 0;
		tmp = tmp->next;
	}
	printf("\n");
}