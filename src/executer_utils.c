/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:04:48 by itorres-          #+#    #+#             */
/*   Updated: 2023/05/10 09:05:38 by itorres-         ###   ########.fr       */
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