/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:38:15 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/19 17:35:57 by crigonza         ###   ########.fr       */
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

void child1(pid_t pid, int *fd, char **command, char **envp)
{
	printf("1-%s\n", command[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (pid > 0)
		waitpid(pid, NULL, 0);
	else if (pid == 0)
		execve(command[0], command, envp);
}

void child2(pid_t pid, int *fd, char **command, char **envp)
{
	printf("2-%s\n", command[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	if (pid > 0)
		waitpid(pid, NULL, 0);
	else if (pid == 0)
		execve(command[0], command, envp);
}

int 	child_exe(int *fd, char **command, char **envp, int status)
{
	if (fd[2] != STDOUT_FILENO)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
	}
	status = execve(command[0], command, envp);
	return(status);
}

void execute_pipe(t_command *comm)
{
	int status;
	pid_t pid;
	pid_t pid2;

	pipe(comm->fd);
	pid = fork();
	if (pid < 0)
		exit (EXIT_FAILURE);
	if (pid == 0)
	{
		printf("1-%s\n", comm->command->command[0]);
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
			printf("2-%s\n", comm->command->next->command[0]);
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

/* void	execute_pipe(t_command *comm)
{
	pid_t	pid;
	pid_t	pid2;
	t_full_comm *tmp;	

	tmp = comm->command;
	if (pipe(comm->fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	child1(pid, comm->fd, tmp->command, comm->envp);
	pid2 = fork();
	tmp = tmp->next;
	child2(pid2, comm->fd, tmp->command, comm->envp);
	//close(fd[0]);
	//close(fd[1]);
	if(pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("1-%s\n", tmp->command[0]);
		close(comm->fd[0]);
		dup2(comm->fd[1], STDOUT_FILENO);
		executer(tmp->command);
		//execve(tmp->command[0], tmp->command, NULL);
		//close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("2-%s\n", tmp->next->command[0]);
		close(comm->fd[1]);
		dup2(comm->fd[0], STDIN_FILENO);
		executer(tmp->next->command);
		//waitpid(pid, NULL, 0);
		//execve(tmp->next->command[0], tmp->next->command, NULL);
		//close(comm->fd[0]);
		//exit(EXIT_SUCCESS);
	} 
}*/