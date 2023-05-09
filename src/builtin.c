/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:26:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/09 11:16:27 by crigonza         ###   ########.fr       */
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

void	pwd_builtin(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	g_exit_value = 0;
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
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(command[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_value = 127;
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
	if (command[1])
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
