/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:33 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 23:32:53 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_line(t_heredoc **hrdc, t_heredoc *new_hrdc)
{
	t_heredoc	*tmp;

	tmp = *hrdc;
	if (*hrdc == NULL)
		*hrdc = new_hrdc;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_hrdc;
	}
}

t_heredoc	*new_doc(char *str)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->line = ft_strdup(str);
	new->next = NULL;
	return (new);
}

void	free_hrdc(t_heredoc **hrdc)
{
	t_heredoc	*tmp;

	while ((*hrdc) != NULL)
	{
		tmp = *hrdc;
		(*hrdc) = (*hrdc)->next;
		free(tmp->line);
		free(tmp);
	}
}

void	print_heredoc(t_heredoc **hrdc)
{
	t_heredoc	*tmp;

	tmp = *hrdc;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
	free_hrdc(hrdc);
}

void	heredoc(char *limit)
{
	char		*line;
	t_heredoc	*heredoc;

	heredoc = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strlen(line) > 0)
		{
			if (ft_strncmp(limit, line, ft_strlen(line)) != 0)
				add_line(&heredoc, new_doc(line));
			else
			{
				free(line);
				break ;
			}
			free(line);
		}
	}
	print_heredoc(&heredoc);
	free(heredoc);
}
