/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:54:42 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/05 13:55:26 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_builtin(t_ev **envp, char **command)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (command[1])
	{
		while (command[1][i] != '=')
			i++;
		if (command[1][i] == '=' && i != 0)
		{
			value = ft_strdup(&command[1][i + 1]);
			key = malloc(sizeof(char) * i + 1);
			ft_strlcpy(key, command[1], i + 1);
			if (!check_key(envp, key, value))
				export(envp, key, value);
		}
	}
	else
		export_whout_args(envp);
}
