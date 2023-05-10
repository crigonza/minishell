/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:21:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 23:48:59 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

void	change_pwd(t_ev **envp, char *path)
{
	t_ev	*pwd;
	t_ev	*old_pwd;

	pwd = *envp;
	old_pwd = *envp;
	while (pwd != NULL)
	{
		if (!ft_strncmp(pwd->key, "PWD", 3))
			break ;
		pwd = pwd->next;
	}
	while (old_pwd != NULL)
	{
		if (!ft_strncmp(old_pwd->key, "OLDPWD", 6))
		{
			free(old_pwd->value);
			old_pwd->value = ft_strdup(pwd->value);
			break ;
		}
		old_pwd = old_pwd->next;
	}
	free (pwd->value);
	pwd->value = ft_strdup(path);
}

void	cd_home(t_ev **envp)
{
	t_ev	*tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->key, "HOME", 4))
		{
			chdir(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	change_pwd(envp, tmp->value);
	g_exit_value = 0;
}

void	cd_builtin(t_ev **envp, char **command)
{
	int		val;
	char	*cd;

	if (!command[1])
		cd_home(envp);
	else
	{
		val = chdir(command[1]);
		if (val == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(command[1], 2);
			ft_putendl_fd("no such file or directory", 2);
			g_exit_value = 1;
		}
		else
		{
			cd = getcwd(NULL, 0);
			change_pwd(envp, cd);
			free(cd);
			g_exit_value = 0;
		}
	}
	
}
