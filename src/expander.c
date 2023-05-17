/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/17 11:59:27 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

char	*expand_envp(char *content, char *key, char *value)
{
	char	*expanded;
	char	*back;

	back = ft_substr(content, ft_strlen(key), ft_strlen(content));
	expanded = ft_strjoin(value, back);
	free(back);
	return (expanded);
}

char	*get_envp(t_ev **env, char *content)
{
	char	*expanded;
	t_ev	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->key, content, ft_strlen(tmp->key)))
		{
			expanded = expand_envp(content, tmp->key, tmp->value);
			return (expanded);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	expand_ret_val(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->content, "$?", ft_strlen(tmp->content)))
		{
			free(tmp->content);
			if (g_exit_value == 256 || g_exit_value == 1)
				tmp->content = ft_itoa(1);
			else if (g_exit_value == 127)
				tmp->content = ft_itoa(127);
			else if (g_exit_value == 0)
				tmp->content = ft_itoa(0);
			else if (g_exit_value == 130)
				tmp->content = ft_itoa(130);
			else if (g_exit_value == 131)
				tmp->content = ft_itoa(131);
		}
		tmp = tmp->next;
	}
}

char	*expand_aux(t_ev **envp, char *content, int len)
{
	char	*aux;
	char	*tmp;

	aux = (char *)malloc(sizeof(char) * len + 1);
	ft_strlcpy(aux, content, len + 1);
	tmp = get_envp(envp, &content[len + 1]);
	if (tmp != NULL)
	{
		aux = ft_strjoin(aux, tmp);
		free (tmp);
	}	
	return (aux);
}

void	expander(t_lexer **lexer, t_ev **envp)
{
	t_lexer	*tmp;
	int		i;

	tmp = *lexer;
	expand_ret_val(lexer);
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '$')
				tmp->content = expand_dollar(envp, tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	parser(lexer, envp);
}
