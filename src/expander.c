/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 23:32:14 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

char	*expand_envp(char *content, char *key, char *value)
{
	int		i;
	char	*expanded;
	char	*expanded_out;
	char	*back;

	i = 0;
	expanded_out = NULL;
	if (content[i] != '$')
	{
		while (content[i] != '$')
			i++;
		expanded = malloc(sizeof(i) + 1);
		ft_strlcpy(expanded, content, i + 1);
		expanded_out = ft_strjoin(expanded, value);
		free(expanded);
	}
	else
		expanded = value;
	back = ft_strnstr(content, key, ft_strlen(content)) + ft_strlen(key);
	if (expanded_out != NULL && back != NULL)
		expanded = ft_strjoin(expanded_out, back);
	free(content);
	free(expanded_out);
	return (expanded);
}

char	*get_envp(t_ev **env, char *content)
{
	char	*var;
	char	*expanded;
	t_ev	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	var = ft_strchr(content, '$') + 1;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->key, var, ft_strlen(tmp->key)))
		{
			expanded = expand_envp(content, tmp->key, tmp->value);
			return (expanded);
		}
		tmp = tmp->next;
	}
	while (content[i] != '$')
		i++;
	expanded = malloc(sizeof(i + 1));
	ft_strlcpy(expanded, content, i + 1);
	free(content);
	return (expanded);
}

int	check_squotes(char *str)
{
	int	i;
	int	quote;
	int	dollar;

	i = 0;
	quote = 0;
	dollar = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			if (quote == 1 && dollar == 1)
				return (1);
			else if (quote == 0)
				quote = 1;
		}
		else if (str[i] == '$' && quote == 1)
			dollar = 1;
		i++;
	}
	return (0);
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
		}
		tmp = tmp->next;
	}
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
		while (tmp->content[i] != '\0')
		{
			if (tmp->content[i] == '$')
			{
				if (!check_squotes(tmp->content))
					tmp->content = get_envp(envp, tmp->content);
			}
			i++;
		}
		tmp = tmp->next;
	}
	print_lexer(lexer);
	parser(lexer, envp);
}
