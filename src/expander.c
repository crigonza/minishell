/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/17 19:30:14 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_envp_2(char *content, char *expanded)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (content[i] != '$')
		i++;
	i++;
	while ((content[i] >= 'A' && content[i] <= 'Z') || content[i] == '('
		|| content[i] == ')')
		i++;
	if (!content[i])
		return (expanded);
	else
	{
		while (content[i])
		{
			i++;
			j++;
		}
		tmp = malloc(sizeof(j + 1));
		ft_strlcpy(tmp, &content[i - j], j + 1);
		expanded = ft_strjoin(expanded, tmp);
		return (expanded);
	}
}
char	*get_envp(char *content, t_list **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*expanded;

	i = 0;
	key = get_envp_key(content);
	value = get_envp_value(envp, key);
	if (content[i] != '$')
	{
		while (content[i] != '$')
			i++;
		expanded = malloc(sizeof(i) + 1);
		ft_strlcpy(expanded, content, i + 1);
		expanded = ft_strjoin(expanded, value);
	}
	else
		expanded = value;
	expanded = get_envp_2(content, expanded);
	//printf("%s----%d\n", expanded, i);
	return (expanded);
}

char	*get_envp_key(char *content)
{
	char	*envp_key;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (content[i] != '$')
		i++;
	if (content[i + 1] == '(')
		i += 2;
	else
		i++;
	while (content[i] >= 'A' && content[i] <= 'Z')
	{
		i++;
		j++;
	}
	envp_key = malloc(sizeof(j + 1));
	ft_strlcpy(envp_key, &content[i - j], j + 1);
	return (envp_key);
}

char	*get_envp_value(t_list **envp, char *search)
{
	char	*value;
	char	*tmp;
	t_list 	*aux;

	aux = *envp;
	while (aux != NULL)
	{
		if (!ft_strncmp(aux->content, search, ft_strlen(search)))
			break ;
		aux = aux->next;
	}
	tmp = ft_strchr(aux->content, '=') + 1;
	value = malloc(sizeof(ft_strlen(tmp) + 1));
	ft_strlcpy(value, tmp, ft_strlen(tmp) + 1);
	return (value);
}

void	expander(t_lexer **lexer, t_list **envp)
{
	t_lexer	*tmp;
	int		i;

	tmp = *lexer;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->content[i] != '\0')
		{
			if (tmp->content[i] == '$')
			{
				tmp->content = get_envp(tmp->content, envp);
			}
			i++;
		}
		tmp = tmp->next;
	}
	free(tmp);
	print_lexer(lexer);
	parser(lexer, envp);
}

void	retokenize(t_lexer **lexer, t_list **envp)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = *lexer;
	while (tmp != NULL)
	{
		if (tmp->token_type == COMMAND)
		{
			while (tmp->content[i])
			{
				if (tmp->content[i] == '/')
					tmp->token_type = PATH;
				if (tmp->content[i] == '$')
					tmp->token_type = STRING;
				i++;
			}
		}
		tmp = tmp->next;
	}
	free(tmp);
	full_path(lexer);
	expander(lexer, envp);
}

void	full_path(t_lexer **lexer)
{
	t_lexer *tmp;

	tmp = *lexer;
	if (tmp->token_type == COMMAND)
	{
		if(ft_strncmp("/bin/", tmp->content, 5) != 0)
			tmp->content = ft_strjoin("/bin/", tmp->content);
	}
	while(tmp != NULL)
	{
		if (tmp->token_type == PIPE)
		{
			tmp = tmp->next;
			full_path(&tmp);
		}
		tmp = tmp->next;
	}
}
