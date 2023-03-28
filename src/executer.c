/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:38:15 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/28 10:12:57 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void solo_cmd(char **command, char **envp)
{
	pid_t	pid;
	int		val;
	
	pid = fork();
	if(pid < 0)
			perror("Error");
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else if (pid == 0)
	{
		val = execve(command[0], command, NULL);
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
	if(tmp->next == NULL)
	{
		if(!is_builtin(tmp->command[0]))
			solo_cmd(tmp->command, env);
		else
			builtin_exe(tmp->command, cmd->env);
		free_env_array(env);
	}
	else
		execute(cmd, env);
}

void execute(t_command *cmd, char **env)
{
	t_full_comm *tmp;
	int prpipe;

	prpipe = dup(0);
	tmp = cmd->command;
	
	while (tmp != NULL)
	{
		if (tmp->pipe_next == 1)
		{
			if(!is_builtin(tmp->command[0]))
				first_child(tmp->command, env, &prpipe);
			else
				builtin_pipe(tmp->command, cmd->env, &prpipe);
		}
		else
			last_child(tmp->command, env, prpipe);
		while (wait(NULL) != -1);
		tmp = tmp->next;
	}
	free_env_array(env);
}
