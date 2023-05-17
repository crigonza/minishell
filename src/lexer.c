/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:39:59 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/17 11:46:52 by crigonza         ###   ########.fr       */
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
		if (ft_isprint(prompt[i]) && prompt[i] != '|' && prompt[i] != '<'
			&& prompt[i] != '>')
			i += get_command(&lexer, &prompt[i]);
		else
			i += set_tokens(prompt[i], prompt[i + 1], &lexer);
	}
	if (lexer != NULL)
	{
		full_path(&lexer, envp);
		expander(&lexer, envp);
	}
	free_lexer(&lexer);
}

t_lexer	*new_token(char *content, int e_token_type)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->e_token_type = e_token_type;
	new->next = NULL;
	return (new);
}
