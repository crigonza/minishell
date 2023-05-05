/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:30:30 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/05 13:35:41 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	close_quotes(char *prompt)
{
	int	quote;
	int	i;

	i = 1;
	quote = 0;
	while (prompt[i])
	{
		if (prompt[i] == 34)
			quote = 1;
		i++;
	}
	return (quote);
}

int	check_echo_opt(t_lexer **lexer, char *prompt)
{
	int	i;

	i = 2;
	if (!ft_strncmp(prompt, "-n", 2) && prompt[i] == ' ')
	{
		add_token(lexer, new_token("-n", COMMAND));
		while (prompt[i] == ' ' || prompt[i] == '\t')
			i++;
		return (i);
	}
	else
		return (0);
}

int	get_echo_string(t_lexer **lexer, char *prompt)
{
	int		i;
	char	*str;

	i = 0;
	if (prompt[i] == 34 && close_quotes(&prompt[i]) == 1)
	{
		return (i);
	}
	else
	{
		while ((prompt[i]) && (prompt[i] != '|') \
				&& (prompt[i] != '<') && (prompt[i] != '>'))
			i++;
		if (prompt[i] == '|' && prompt[i - 1] == ' ')
		{
			i--;
			while (prompt[i - 1] == ' ')
				i--;
		}
		str = malloc(sizeof(i + 1));
		ft_strlcpy(str, prompt, i + 1);
		add_token(lexer, new_token(str, STRING));
		free(str);
	}
	return (i);
}

int	get_command(t_lexer **lexer, char *prompt)
{
	char	*str;
	int		i;

	i = 0;
	while (prompt[i] == '-')
		i++;
	while (prompt[i] && prompt[i] != '\t' \
		&& prompt[i] != ' ' && prompt[i] != '|' \
		&& prompt[i] != '<' && prompt[i] != '>')
		i++;
	str = malloc(sizeof(i + 1));
	ft_strlcpy(str, prompt, i + 1);
	add_token(lexer, new_token(str, COMMAND));
	if (!ft_strncmp(str, "echo", 4))
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
