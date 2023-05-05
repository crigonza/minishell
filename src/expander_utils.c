/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:37:14 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/05 13:37:49 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

void	sintax_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	g_exit_value = 127;
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
	if (!full_path(lexer, envp))
		expander(lexer, envp);
	else
		sintax_error((*lexer)->content);
}

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

int	get_full_path(char **path, t_lexer *lex)
{
	int		i;
	char	*aux;
	char	*pth;

	i = 0;
	if (lex->token_type == COMMAND && !is_builtin(lex->content))
	{
		while (path[i])
		{
			pth = ft_strjoin(path[i], "/");
			aux = ft_strjoin(pth, lex->content);
			if (!access(aux, X_OK))
			{
				free(lex->content);
				lex->content = aux;
				break ;
			}
			free(aux);
			free(pth);
			i++;
		}
		if (!path[i])
			return (1);
	}
	return (0);
}

int	full_path(t_lexer **lexer, t_ev **env)
{
	t_lexer	*tmp;
	char	*path;
	char	**split_path;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	tmp = *lexer;
	path = get_path(env);
	if (path != NULL)
	{
		split_path = ft_split(path, ':');
		ret = get_full_path(split_path, tmp);
		while (split_path[i])
		{
			free(split_path[i]);
			i++;
		}
		free(split_path);
		if (ret == 1)
			return (ret);
		while (tmp != NULL)
		{
			if (tmp->token_type == PIPE)
			{
				tmp = tmp->next;
				full_path(&tmp, env);
			}
			tmp = tmp->next;
		}
	}
	return (ret);
}