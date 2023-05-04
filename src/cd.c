/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:21:47 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/04 13:46:13 by itorres-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/minishell.h"

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
}

void	cd_builtin(t_ev **envp, char **command)
{
	int		val;
	char	*buff;

	if (!command[2])
	{
		val = chdir(command[1]);
		if (val == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putendl_fd(command[1], 2);
		}
		else
		{
			buff = getcwd(NULL, 0);
			change_pwd(envp, buff);
			free(buff);
		}
	}
	else if (!command[1])
		cd_home(envp);
	else
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(command[1], 2);
	}
}
