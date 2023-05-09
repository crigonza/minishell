/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:54:42 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/09 11:02:30 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

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
	g_exit_value = 0;
	
}

void 	change_values(t_ev *current, t_ev *next)
{
	char	*aux_key;
	char	*aux_value;

	aux_key = ft_strdup(current->key);
	aux_value = ft_strdup(current->value);
	free(current->key);
	free(current->value);
	current->key = ft_strdup(next->key);
	current->value = ft_strdup(next->value);
	free(next->key);
	free(next->value);
	next->key = ft_strdup(aux_key);
	next->value = ft_strdup(aux_value);
	free(aux_key);
	free(aux_value);
}
