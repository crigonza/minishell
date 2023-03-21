/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:38:15 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/21 10:59:49 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void executer(char **command, char **envp)
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

void	child_exe(int *fd, char **command, char **envp, int isfirst)
{
	int val;

	printf("%s\n", command[0]);
	if (isfirst == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	val = execve(command[0], command, envp);
	if (val == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);

}

void execute(t_command *comm)
{
	pid_t pid;
	pid_t pid2;

	if(pipe(comm->fd) == -1)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		perror("pid");
	if (pid == 0)
	{
		child_exe(comm->fd, comm->command->command, comm->envp, comm->first_comm);
		comm->first_comm = 0;
	}
	else
	{
		pid2 = fork();
		if (pid == -1)
			perror("pid2");
		if(pid2 == 0)
			child_exe(comm->fd, comm->command->next->command, comm->envp, comm->first_comm);
		else
		{
			close(comm->fd[0]);
			close(comm->fd[1]);
			waitpid(pid, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}

}

void execute_pipe(t_command *comm)
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
}

