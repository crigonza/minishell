/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:21:49 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 23:48:33 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

int	is_builtin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
		return (1);
	else
		return (0);
}

void	builtin_exe_pid(t_full_comm *cmd, t_ev **envp)
{
	pid_t	pid;
	char	*com;

	pid = fork();
	com = cmd->command[0];
	if (pid == 0)
	{
		redir_solo_cmd(cmd);
		if (!ft_strncmp("echo", com, ft_strlen(com)))
			echo_builtin(cmd->command);
		else if (!ft_strncmp("pwd", com, ft_strlen(com)))
			pwd_builtin();
		else if (!ft_strncmp("env", com, ft_strlen(com)))
			env_builtin(envp, cmd->command);
		exit(g_exit_value);
	}
	else
		waitpid(pid, &g_exit_value, 0);
}

void	last_builtin_pipe(t_full_comm *cmd, t_ev **envp, int prpipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(prpipe, STDIN_FILENO);
		close(prpipe);
		builtin_exe(cmd, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(prpipe);
		waitpid(pid, &g_exit_value, 0);
	}
}

void	builtin_pipe(t_full_comm *cmd, t_ev **envp, int *prpipe)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		dup2(*prpipe, STDIN_FILENO);
		close(*prpipe);
		builtin_exe(cmd, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		close(*prpipe);
		*prpipe = fd[0];
		waitpid(pid, &g_exit_value, 0);
	}
}

int	check_key(t_ev **env, char *key, char *value)
{
	t_ev	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key)))
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
