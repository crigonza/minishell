/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:37:14 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/17 11:49:55 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

char	*get_path(t_ev **env)
{
	t_ev	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->key, "PATH", 4))
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NULL);
	return (tmp->value);
}

void	get_full_path(char **path, t_lexer *lex)
{
	int		i;
	char	*aux;
	char	*pth;

	i = 0;
	if (lex->e_token_type == COMMAND && !is_builtin(lex->content))
	{
		while (path[i])
		{
			pth = ft_strjoin(path[i], "/");
			aux = ft_strjoin(pth, lex->content);
			if (!access(aux, X_OK))
			{
				free(lex->content);
				free(pth);
				lex->content = aux;
				break ;
			}
			free(aux);
			free(pth);
			i++;
		}
	}
}

void	full_path_aux(t_lexer **lexer, t_ev **env)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp != NULL)
	{
		if (tmp->e_token_type == PIPE)
		{
			tmp = tmp->next;
			full_path(&tmp, env);
		}
		tmp = tmp->next;
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
	if (path != NULL)
	{
		split_path = ft_split(path, ':');
		get_full_path(split_path, tmp);
		while (split_path[i])
		{
			free(split_path[i]);
			i++;
		}
		free(split_path);
		full_path_aux(lexer, env);
	}
}

int	check_squotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 && i > 2)
			return (1);
		i++;
	}
	return (0);
}
