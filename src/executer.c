/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:38:15 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/25 08:37:36 by crigonza         ###   ########.fr       */
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

/* void	child_exe(char **command, char **envp, int *fd)
{
	pid_t pid;
	int res;

	pid = fork();
	if (pid < 0)
	{
		perror("pid");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		res = execve(command[0], command, envp);
		if (res == -1)
			perror("execve");
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
} */

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

void inbuilt_pipe(char **cmd, char **envp, int *prpipe)
{
	int fd[2];

	pipe(fd);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	//dup2(*prpipe, STDIN_FILENO);
	//close(*prpipe);
	builtin_exe(cmd, envp);
	//close(fd[1]);
	//close (*prpipe);
	//*prpipe = fd[0];
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

void execute(t_command *cmd)
{
	t_full_comm *tmp;
	int prpipe;

	prpipe = dup(0);
	tmp = cmd->command;
	if(tmp->next == NULL)
	{
		if(!is_builtin(tmp->command[0]))
			solo_cmd(tmp->command, cmd->envp);
		else
			builtin_exe(tmp->command, cmd->envp);
	}
	else
	{
		while (tmp != NULL)
		{
			if (tmp->pipe_next == 1)
			{
				if(!is_builtin(tmp->command[0]))
					first_child(tmp->command, cmd->envp, &prpipe);
				else
					inbuilt_pipe(tmp->command, cmd->envp, &prpipe);
			}
			else
				last_child(tmp->command, cmd->envp, prpipe);
			tmp = tmp->next;
		}
	}
}

/* void execute_pipe(t_command *comm)
{
	pid_t pid;
	pid_t pid2;
	int status;
	
	if(pipe(comm->fd) == -1)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid < 0)
		exit (EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(comm->fd[1], STDOUT_FILENO);
		close(comm->fd[0]);
		close(comm->fd[1]);
		status = execve(comm->command->command[0], comm->command->command, comm->envp);
		if (status == -1)
			{
				perror("execve1");
				exit(EXIT_FAILURE);
			}
			else
				exit(EXIT_SUCCESS);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(comm->fd[0], STDIN_FILENO);
			close(comm->fd[1]);
			close(comm->fd[0]);
			status = execve(comm->command->next->command[0], comm->command->next->command, comm->envp);
			if (status == -1)
			{
				perror("execve2");
				exit(EXIT_FAILURE);
			}
			else
				exit(EXIT_SUCCESS);
		}
		else
		{
			close(comm->fd[0]);
			close(comm->fd[1]);
			waitpid(pid, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
} */

