/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:26:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/12 17:02:49 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

void	echo_builtin(char **command)
{
	if (!command[1])
		ft_putchar_fd('\n', 1);
	else
	{
		if (!ft_strncmp(command[1], "-n", 2))
			ft_putstr_fd(command[2], 1);
		else
			ft_putendl_fd(command[1], 1);
	}
	g_exit_value = 0;
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

void	builtin_exe(t_full_comm *cmd, t_ev **envp)
{
	char	*com;

	com = cmd->command[0];
	if (!ft_strncmp("export", com, ft_strlen(com)))
		export_builtin(envp, cmd->command);
	else if (!ft_strncmp("unset", com, ft_strlen(com)))
		unset_builtin(envp, cmd->command);
	else if (!ft_strncmp("cd", com, ft_strlen(com)))
		cd_builtin(envp, cmd->command);
	else
	{
		builtin_exe_pid(cmd, envp);
	}
}
