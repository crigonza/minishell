/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:30:30 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/10 23:33:01 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_echo_string(t_lexer **lexer, char *prompt)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = close_quotes(prompt);
	if (quotes > 0)
	{
		i = with_quotes(lexer, prompt, quotes);
	}
	else
		i = without_quotes(lexer, prompt);
	return (i);
}

int	get_command(t_lexer **lexer, char *prompt)
{
	char	*str;
	int		i;

	i = 0;
	while (prompt[i] == '-')
		i++;
	while (prompt[i] && prompt[i] != '\t' && prompt[i] != ' '
		&& prompt[i] != '|' && prompt[i] != '<' && prompt[i] != '>')
		i++;
	str = malloc(sizeof(i + 1));
	ft_strlcpy(str, prompt, i + 1);
	add_token(lexer, new_token(str, COMMAND));
	if (!ft_strncmp(str, "echo", 4) && prompt[4])
	{
		while (prompt[i] == ' ' || prompt[i] == '\t')
			i++;
		i += check_echo_opt(lexer, &prompt[i]);
		i += get_echo_string(lexer, &prompt[i]);
	}
	free(str);
	return (i);
}

int	set_tokens(char first, char next, t_lexer **lexer)
{
	if (first == '|')
		add_token(lexer, new_token("|", PIPE));
	if (first == '<')
	{
		if (next == '<')
		{
			add_token(lexer, new_token("<<", D_LESS_THAN));
			return (2);
		}
		else
			add_token(lexer, new_token("<", LESS_THAN));
	}
	if (first == '>')
	{
		if (next == '>')
		{
			add_token(lexer, new_token(">>", D_GREATER_THAN));
			return (2);
		}
		else
			add_token(lexer, new_token(">", GREATER_THAN));
	}
	return (1);
}
