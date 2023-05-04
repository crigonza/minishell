/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:39:59 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/04 10:56:08 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;

	while ((*lexer) != NULL)
	{
		tmp = *lexer;
		(*lexer) = (*lexer)->next;
		free(tmp->content);
		free(tmp);
	}
}

int	get_string(t_lexer **lexer, char *prompt)
{
	char	*str;
	int		i;

	i = 1;
	while (prompt[i] != 34)
		i++;
	str = malloc(sizeof(i + 1));
	ft_strlcpy(str, prompt, i + 1);
	add_token(lexer, new_token(str, STRING));
	free(str);
	return (i + 2);
}

int close_quotes(char *prompt)
{
	int quote;
	int i;

	i = 1;
	quote = 0;
	while(prompt[i])
	{
		if(prompt[i] == 34)
			quote = 1;
		i++;
	}
	return(quote);
}

int	check_echo_opt(t_lexer **lexer, char *prompt)
{
	int i;

	i = 2;
	if (!ft_strncmp(prompt, "-n", 2) && prompt[i] == ' ')
	{
		add_token(lexer, new_token("-n", COMMAND));
		while(prompt[i] == ' ' || prompt[i] == '\t')
			i++;
		return(i);	
	}
	else
		return(0);
}

int	get_echo_string(t_lexer **lexer, char *prompt)
{
	int	i;
	char *str;

	i = 0;
	if (prompt[i] == 34 && close_quotes(&prompt[i]) == 1)
	{
		return(i);
	}
	else
	{
		while(prompt[i] && prompt[i] != '|' && prompt[i] != '<' && prompt[i] != '>')
			i++;
		if(prompt[i] == '|' && prompt[i - 1] == ' ')
		{
			i--;
			while(prompt[i - 1] == ' ')
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
	while (prompt[i] && prompt[i] != '\t' && prompt[i] != ' ' && prompt[i] != '|' && prompt[i] != '<' && prompt[i] != '>')
		i++;
	str = malloc(sizeof(i + 1));
	ft_strlcpy(str, prompt, i + 1);
	add_token(lexer, new_token(str, COMMAND));
	if (!ft_strncmp(str, "echo", 4))
	{
		while(prompt[i] == ' ' || prompt[i] == '\t')
		i++;
		i += check_echo_opt(lexer, &prompt[i]);
		i += get_echo_string(lexer, &prompt[i]);
	}
	free(str);
	return (i);
}

int 	set_tokens(char first, char next, t_lexer **lexer)
{
	if (first == '|')
		add_token(lexer, new_token("|", PIPE));
	if (first == '<')
	{
		if(next == '<')
		{
			add_token(lexer, new_token("<<", D_LESS_THAN));
			return (2);
		}
		else
			add_token(lexer, new_token("<", LESS_THAN));
	}
	if (first == '>')
	{
		if(next == '>')
		{
			add_token(lexer, new_token(">>", D_GREATER_THAN));
			return 2;
		}
		else
			add_token(lexer, new_token(">", GREATER_THAN));
	}
	return (1);
}

void	init_lexer(char *prompt, t_ev **envp)
{
	int		i;
	t_lexer	*lexer;

	i = 0;
	lexer = NULL;
	while (prompt[i] != '\0')
	{
		while(prompt[i] == ' ' || prompt[i] == '\t')
			i++;
		if (prompt[i] == 34)
			i += get_string(&lexer, &prompt[i + 1]);
		if (ft_isprint(prompt[i]) && prompt[i] != '|' && prompt[i] != '<' && prompt[i] != '>')
			i += get_command(&lexer, &prompt[i]);
		else
			i += set_tokens(prompt[i],prompt[i + 1], &lexer);
	}
	print_lexer(&lexer);
	if(lexer != NULL)
		retokenize(&lexer, envp);
	free_lexer(&lexer);
}

t_lexer	*new_token(char *content, int token_type)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->token_type = token_type;
	new->next = NULL;
	return (new);
}

void	add_token(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lexer;
	if (*lexer == NULL)
		*lexer = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
