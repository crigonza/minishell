/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:38:15 by crigonza          #+#    #+#             */
/*   Updated: 2023/04/24 17:17:18 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int exit_value;

void solo_cmd(t_full_comm *cmd, char **envp)
{
	pid_t	pid;
	int		val;
	
	pid = fork();
	if(pid < 0)
			perror("Error");
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	else if (pid == 0)
	{
		redir_solo_cmd(cmd);
		val = execve(cmd->command[0], cmd->command, envp);
		if (val == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else 
			exit(EXIT_SUCCESS);
	}
}

void first_child(char **cmd, char **envp, int *prpipe)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		dup2(*prpipe, STDIN_FILENO);
		close(*prpipe);
		execve(cmd[0], cmd, envp);
	}
	else
	{
		close(fd[1]);
		close (*prpipe);
		*prpipe = fd[0];
	}
}

void last_child(char **cmd, char **envp, int prpipe)
{
	pid_t pid;

	pid = fork();
	if(pid == 0)
	{
		dup2 (prpipe, STDIN_FILENO);
		close(prpipe);
		execve(cmd[0], cmd, envp);
	}
	else
	{
		close(prpipe);
		while (wait(NULL) != -1);
	}
}

void exe_init(t_command *cmd)
{
	t_full_comm *tmp;
	char **env;

	env = convert_envp(cmd->env);
	tmp = cmd->command;
	while (tmp != NULL)
	{
		if(tmp->next == NULL || tmp->semic_next == 1)
			execute_semi(&tmp, cmd->env, env);
		else if(tmp->pipe_next == 1)
			tmp = execute_pipe(&tmp, cmd->env, env);
		if (tmp != NULL)
			tmp = tmp->next;
	}
	free_env_array(env);
}

void execute_semi(t_full_comm **cmd,t_ev **l_env, char **env)
{
	t_full_comm *tmp;

	tmp = *cmd;
	if(!is_builtin(tmp->command[0]))
	{
		if(!check_redir(tmp))
			solo_cmd(tmp, env);
	}
	else
	{
		if(!check_redir(tmp))
			builtin_exe(tmp, l_env);
	}
}

t_full_comm *execute_pipe(t_full_comm **cmd, t_ev **l_env, char **env)
{
	t_full_comm *tmp;
	int prpipe;

	prpipe = dup(0);
	tmp = *cmd;
	while (tmp != NULL)
	{
		if (tmp->pipe_next == 1)
		{
			if(!is_builtin(tmp->command[0]))
				first_child(tmp->command, env, &prpipe);
			else
				builtin_pipe(tmp, l_env, &prpipe);
		}	
		else
			last_child(tmp->command, env, prpipe);
		while (wait(NULL) != -1);
		if (tmp->semic_next == 1)
			break;
		tmp = tmp->next;
	}
	return(tmp);
}
