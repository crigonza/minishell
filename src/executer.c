/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:38:15 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 23:31:50 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

void	first_child(t_full_comm *cmd, char **envp, int *prpipe)
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
		redir_solo_cmd(cmd);
		if (execve(cmd->command[0], cmd->command, envp) == -1)
			syntax_error(cmd->command[0]);
	}
	else
	{
		close(fd[1]);
		close(*prpipe);
		*prpipe = fd[0];
		waitpid(-1, &g_exit_value, 0);
	}
}

void	last_child(t_full_comm *cmd, char **envp, int prpipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(prpipe, STDIN_FILENO);
		close(prpipe);
		redir_solo_cmd(cmd);
		if (execve(cmd->command[0], cmd->command, envp) == -1)
			syntax_error(cmd->command[0]);
	}
	else
	{
		close(prpipe);
		waitpid(pid, &g_exit_value, 0);
	}
}

void	exe_init(t_command *cmd)
{
	t_full_comm	*tmp;
	char		**env;

	env = convert_envp(cmd->env);
	tmp = cmd->command;
	if (tmp->pipe_next == 1)
		execute_pipe(&tmp, cmd->env, env);
	else
		execute(&tmp, cmd->env, env);
	if (g_exit_value > 1 && g_exit_value != 256)
		g_exit_value = 127;
	free_env_array(env);
}

void	execute(t_full_comm **cmd, t_ev **l_env, char **env)
{
	t_full_comm	*tmp;

	tmp = *cmd;
	if (!check_redir(tmp))
	{
		if (!is_builtin(tmp->command[0]))
			solo_cmd(tmp, env);
		else
			builtin_exe(tmp, l_env);
	}
}

void	execute_pipe(t_full_comm **cmd, t_ev **l_env, char **env)
{
	t_full_comm	*tmp;
	int			prpipe;

	prpipe = dup(0);
	tmp = *cmd;
	while (tmp != NULL)
	{
		check_redir(tmp);
		if (tmp->pipe_next == 1)
		{
			if (!is_builtin(tmp->command[0]))
				first_child(tmp, env, &prpipe);
			else
				builtin_pipe(tmp, l_env, &prpipe);
		}
		else
		{
			if (!is_builtin(tmp->command[0]))
				last_child(tmp, env, prpipe);
			else
				last_builtin_pipe(tmp, l_env, prpipe);
		}
		tmp = tmp->next;
	}
}
