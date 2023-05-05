/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:41:12 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/05 13:41:45 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_envp(char **envp, t_ev **env)
{
	int		i;
	int		j;
	char	**vars;

	i = 0;
	while (envp[i])
	{
		vars = ft_split(envp[i], '=');
		add_ev(env, new_ev(vars[0], vars[1]));
		j = 0;
		while (vars[j])
		{
			free(vars[j]);
			j++;
		}
		free (vars);
		i++;
	}
}
