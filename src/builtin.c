/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:26:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/05 14:02:28 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

void	echo_builtin(char **command)
{
	if (!ft_strncmp(command[1], "-n", 2))
		ft_putstr_fd(command[2], 1);
	else
		ft_putendl_fd(command[1], 1);
}

void	pwd_builtin(char **command)
{
	char	*buff;

	if (!command[1])
	{
		buff = getcwd(NULL, 0);
		ft_putendl_fd(buff, 1);
		free(buff);
		g_exit_value = 0;
	}
	else
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		g_exit_value = 256;
	}
}

void	env_builtin(t_ev **envp, char **command)
{
	t_ev	*tmp;

	tmp = *envp;
	if (!command[1])
	{
		while (tmp != NULL)
		{
			printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
		g_exit_value = 0;
	}
	else
	{
		ft_putendl_fd("env: too many arguments", 2);
		g_exit_value = 256;
	}
}

void	free_tmp(t_ev	*tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	unset_builtin(t_ev **envp, char **command)
{
	t_ev	*tmp;
	t_ev	*prev;

	tmp = *envp;
	if (!command[1])
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		g_exit_value = 256;
	}
	else
	{
		while (tmp != NULL)
		{
			if (!ft_strncmp(tmp->key, command[1], ft_strlen(command[1])))
				break ;
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp != NULL)
		{
			prev->next = tmp->next;
			free_tmp(tmp);
		}
		g_exit_value = 0;
	}
}
