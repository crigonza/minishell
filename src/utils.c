/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:38:34 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/11 09:05:54 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	ev_len(t_ev **env)
{
	int		i;
	t_ev	*tmp;

	i = 0;
	tmp = *env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	get_count(t_lexer **lexer)
{
	t_lexer	*tmp;
	int		count;

	count = 0;
	tmp = *lexer;
	while (tmp != NULL && tmp->e_token_type != PIPE)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

void	free_tmp(t_ev *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	syntax_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}
