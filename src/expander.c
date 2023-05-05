/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/05 13:36:59 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

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
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->key, var, ft_strlen(tmp->key)))
		{
			expanded = expand_envp(content, tmp->key, tmp->value);
			return (expanded);
		}
		tmp = tmp->next;
	}
	expanded = content;
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
			if (g_exit_value == 256)
				tmp->content = ft_itoa(1);
			else if (g_exit_value == 127)
				tmp->content = ft_itoa(127);
			else
				tmp->content = ft_itoa(exit_v(ft_itoa(g_exit_value)));
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
