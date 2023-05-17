/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:51:35 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/17 12:22:04 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_more_dollars(t_ev **envp, char *content)
{
	int		i;
	int		q;
	char	*tmp;

	i = 0;
	q = 0;
	tmp = NULL;
	while (content[i])
	{
		if (content[i] == 39)
			q ++;
		if (q == 2)
			q = 0;
		if ((content[i] == '$' && q == 0)
        || (content[i] == '$' && q == 1 && !check_squotes(&content[i])))
		{
			tmp = expand_dollar(envp, content);
			break ;
		}
		i++;
	}
	if (tmp == NULL)
		return (content);
	return (tmp);
}

char	*expand_dollar(t_ev **envp, char *content)
{
	int		i;
	int		q;
	char	*tmp;

	i = 0;
	q = 0;
	tmp = NULL;
	while (content[i])
	{
		if (content[i] == 39)
			q ++;
		if (q == 2)
			q = 0;
		if ((content[i] == '$' && q == 0)
         || (content[i] == '$' && q == 1 && !check_squotes(&content[i])))
		{
			tmp = expand_aux(envp, content, i);
			break ;
		}
		i++;
	}
	if (tmp != NULL)
        return (expand_dollar_aux(envp, content, tmp));
	return (content);
}

char    *expand_dollar_aux(t_ev **envp, char *content, char *tmp)
{
    char    *aux;

    free (content);
	aux = check_more_dollars (envp, tmp);
    //free (tmp);
	return (aux);
}
