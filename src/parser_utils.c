/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:04 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/05 13:29:04 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	i = 0;
	pipe = 0;
	tmp = *lexer;
	comm = malloc(sizeof(char *) * (get_count(lexer) + 1));
	comm[get_count(lexer)] = NULL;
	while (tmp != NULL && tmp->token_type != PIPE)
	{
		comm[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	if (tmp != NULL && tmp->token_type == PIPE)
		pipe = 1;
	add_command(command, new_command(comm, pipe));
	if (tmp != NULL && tmp->token_type == PIPE)
	{
		tmp = tmp->next;
		parse_command(command, &tmp);
	}
}
