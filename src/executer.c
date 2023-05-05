/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:38:15 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/05 13:39:17 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

void	solo_cmd(t_full_comm *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("Error");
	else if (pid > 0)
	{
		waitpid(pid, &g_exit_value, 0);
	}
	else if (pid == 0)
	{
		redir_solo_cmd(cmd);
		g_exit_value = execve(cmd->command[0], cmd->command, envp);
	}
}

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
		execve(cmd->command[0], cmd->command, envp);
	}
	else
	{
		close(fd[1]);
		close (*prpipe);
		*prpipe = fd[0];
	}
}

void	last_child(t_full_comm *cmd, char **envp, int prpipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2 (prpipe, STDIN_FILENO);
		close(prpipe);
		redir_solo_cmd(cmd);
		execve(cmd->command[0], cmd->command, envp);
	}
	else
	{
		close(prpipe);
		while (wait(NULL) != -1);
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
	/* while (tmp != NULL)
	{
		if(tmp->pipe_next == 1)
			execute_pipe(&tmp, cmd->env, env);
		else
			execute(&tmp, cmd->env, env);
		//if (tmp != NULL)
		tmp = tmp->next;
	} */
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
		while (wait(&g_exit_value) != -1);
		tmp = tmp->next;
	}
}
