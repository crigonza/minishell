/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:34 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 23:34:15 by crigonza         ###   ########.fr       */
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

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	ev_len(t_ev **env)
{
	int		i;
	t_ev	*tmp;

	i = 0;
	tmp = *env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
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
