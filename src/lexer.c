/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:39:59 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/05 13:35:47 by itorres-         ###   ########.fr       */
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

void	init_lexer(char *prompt, t_ev **envp)
{
	int		i;
	t_lexer	*lexer;

	i = 0;
	lexer = NULL;
	while (prompt[i] != '\0')
	{
		while (prompt[i] == ' ' || prompt[i] == '\t')
			i++;
		if (prompt[i] == 34)
			i += get_string(&lexer, &prompt[i + 1]);
		if (ft_isprint(prompt[i]) && prompt[i] != '|' \
			&& prompt[i] != '<' && prompt[i] != '>')
			i += get_command(&lexer, &prompt[i]);
		else
			i += set_tokens(prompt[i], prompt[i + 1], &lexer);
	}
	print_lexer(&lexer);
	if (lexer != NULL)
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
