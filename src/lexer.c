/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:39:59 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/14 20:56:25 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp != NULL)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
}

int	get_string(t_lexer **lexer, char *prompt)
{
	char	*str;
	int		i;

	i = 0;
	while (prompt[i] != 34)
		i++;
	str = malloc(sizeof(i + 1));
	ft_strlcpy(str, prompt, i + 1);
	add_token(lexer, new_token(str, STRING));
	free(str);
	return (i + 1);
}

int	get_command(t_lexer **lexer, char *prompt)
{
	char	*str;
	int		i;

	i = 0;
	while (prompt[i] == '-')
		i++;
	while (prompt[i] && prompt[i] != '\t' && prompt[i] != ' ' && prompt[i] != '|')
		i++;
	str = malloc(sizeof(i + 1));
	ft_strlcpy(str, prompt, i + 1);
	if (prompt[i] == '/')
		add_token(lexer, new_token(str, PATH));
	else
		add_token(lexer, new_token(str, COMMAND));
	free(str);
	return (i);
}

void	init_lexer(char *prompt, t_list **envp)
{
	int		i;
	int		j;
	char	*str;
	t_lexer	*lexer;

	i = 0;
	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	lexer = NULL;
	while (prompt[i] != '\0')
	{
		while(prompt[i] == ' ' || prompt[i] == '\t')
            i++;
		if (prompt[i] == 34)
		{
			i++;
			i += get_string(&lexer, &prompt[i]);
		}
		if (ft_isprint(prompt[i]))
			i += get_command(&lexer, &prompt[i]);
        if (prompt[i] == '|')
		    add_token(&lexer, new_token("|", PIPE));
		i++;
	}
	print_lexer(&lexer);
	lexer->envp = envp;
	retokenize(&lexer, envp);
	free_lexer(&lexer);
}

t_lexer	*new_token(char *content, int token_type)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->content = malloc(sizeof(ft_strlen(content) + 1));
	ft_strlcpy(new->content, content, ft_strlen(content) + 1);
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
		tmp = last_token(*lexer);
		tmp->next = new;
	}
}

t_lexer	*last_token(t_lexer *lexer)
{
	while (lexer->next != NULL)
		lexer = lexer->next;
	return (lexer);
}