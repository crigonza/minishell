/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:04:48 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/17 11:44:15 by crigonza         ###   ########.fr       */
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
		execve(cmd->command[0], cmd->command, envp);
		if (execve(cmd->command[0], cmd->command, envp) == -1)
			syntax_error(cmd->command[0]);
	}
}

void	wait_4_pids(void)
{
	while (waitpid(-1, &g_exit_value, 0) != -1)
	{
	}
}
