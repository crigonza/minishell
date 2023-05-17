/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:13:55 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/17 10:41:30 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*clean_quotes_aux(char *prompt, int quotes, int len)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1 - quotes));
	while (i < len)
	{
		while (prompt[i] == 34)
			i++;
		str[j] = prompt[i];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*clean_quotes(char *prompt, int quotes, int len)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = NULL;
	while (prompt[i] && i < len)
	{
		if (prompt[i] == 39)
			j++;
		i++;
	}
	quotes -= j;
	str = clean_quotes_aux(prompt, quotes, len);
	return (str);
}
