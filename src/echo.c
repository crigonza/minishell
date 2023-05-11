/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:57:40 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/11 12:18:38 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	close_quotes(char *prompt)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (prompt[i])
	{
		if (prompt[i] == 34 || prompt[i] == 39)
			quote++;
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

int	without_quotes(t_lexer **lexer, char *prompt)
{
	int		i;
	char	*str;

	i = 0;
	while ((prompt[i]) && (prompt[i] != '|') && (prompt[i] != '<')
		&& (prompt[i] != '>'))
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
	return (i);
}

char	*clean_quotes(char *prompt, int quotes, int len)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (prompt[i] && i < len)
	{
		if(prompt[i] == 39)
			j++;
		i++;
	}
	quotes -= j;
	j = 0;
	i = 0;
	str = malloc(sizeof(len + 1 - quotes));
	while (i < len)
	{
		while (prompt[i] == 34)
			i++;
		str[j] = prompt[i];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	between_quotes(char *prompt, int quotes)
{
	int	i;

	i = 0;
	while(prompt[i] && quotes != 0)
	{
		if(prompt[i] == 34 || prompt[i] == 39)
			quotes --;
		if(quotes != 0)
			i++;
	}
	return (i);
}

int	with_quotes(t_lexer **lexer, char *prompt, int quotes)
{
	int		i;
	char	*str;

	i = 0;	
	while ((prompt[i]) && (prompt[i] != '|') && (prompt[i] != '<')
		&& (prompt[i] != '>'))
	{
		if((prompt[i] == 34 || prompt[i] == 39) && quotes > 1)
			i += between_quotes(&prompt[i], quotes);
		i++;
	}
	if (prompt[i] == '|' && prompt[i - 1] == ' ')
	{
		i--;
		while (prompt[i - 1] == ' ')
			i--;
	}
	str = clean_quotes(prompt, quotes, i);
	add_token(lexer, new_token(str, STRING));
	free(str);
	return (i);
}
