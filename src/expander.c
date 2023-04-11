/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/04/11 12:21:31 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_envp(char *content, char *key, char *value)
{
	int		i;
	char	*expanded;
	char	*back;

	i = 0;
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
	back = ft_strnstr(content, key, ft_strlen(content)) + ft_strlen(key);
	expanded = ft_strjoin(expanded, back);
	return (expanded);
}

char	*get_envp(t_ev **env, char *content)
{
	char	*var;
	char	*expanded;
	t_ev	*tmp;

	tmp = *env;
	var = ft_strchr(content, '$') + 1;
	while(tmp != NULL)
	{
		if(!ft_strncmp(tmp->key, var, ft_strlen(tmp->key)))
		{
			expanded = expand_envp(content, tmp->key, tmp->value);
			return(expanded);
		}
		tmp = tmp->next;
	}
	expanded = content;
	return (expanded);
}

void	expander(t_lexer **lexer, t_ev **envp)
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
				tmp->content = get_envp(envp, tmp->content);
			}
			i++;
		}
		tmp = tmp->next;
	}
	free(tmp);
	print_lexer(lexer);
	parser(lexer, envp);
}

void	retokenize(t_lexer **lexer, t_ev **envp)
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
				if (tmp->content[i] == '$')
					tmp->token_type = STRING;
				i++;
			}
		}
		tmp = tmp->next;
	}
	free(tmp);
	full_path(lexer, envp);
	expander(lexer, envp);
}

char	*get_path(t_ev **env)
{
	t_ev *tmp;

	tmp = *env;
	while(tmp != NULL)
	{
		if(!ft_strncmp(tmp->key, "PATH", 4))
			break;
		tmp = tmp->next;
	}
	if(tmp == NULL)
		return(NULL);
	return(tmp->value);
}

void	get_full_path(char **path, t_lexer *lex)
{
	int 	i;
	char *aux;

	i = 0;
	if(lex->token_type == COMMAND && !is_builtin(lex->content))
	{
		while(path[i])
		{
			path[i] = ft_strjoin(path[i], "/");
			aux = ft_strjoin(path[i], lex->content);
			if(!access(aux, X_OK))
			{
				free(lex->content);
				lex->content = aux;
				break;
			}
			i++;
		}
	}
}

void	full_path(t_lexer **lexer, t_ev **env)
{
	t_lexer	*tmp;
	char	*path;
	char	**split_path;
	int		i;

	i = 0;
	tmp = *lexer;
	path = get_path(env);
	if(path != NULL)
	{
		split_path = ft_split(path, ':');
		get_full_path(split_path, tmp);
		while(split_path[i])
		{
			free(split_path[i]);
			i++;
		}
		free(split_path);
		while(tmp != NULL)
		{
			if (tmp->token_type == PIPE || tmp->token_type == SEMICOLON)
			{
				tmp = tmp->next;
				full_path(&tmp, env);
			}
			tmp = tmp->next;
		}
	}
}
