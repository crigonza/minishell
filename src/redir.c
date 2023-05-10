/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:49:07 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 21:49:25 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exit_value;

void	file_out(t_full_comm *cmd, int i)
{
	cmd->fileout = cmd->command[i + 1];
	if (!ft_strncmp(cmd->command[i], ">>", 2))
		cmd->fdout = open(cmd->fileout, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (!ft_strncmp(cmd->command[i], ">", 1))
		cmd->fdout = open(cmd->fileout, O_RDWR | O_CREAT | O_TRUNC, 0777);
	cmd->command[i] = NULL;
	if (cmd->fdout == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	file_in(t_full_comm *cmd, int i)
{
	if (!ft_strncmp(cmd->command[i], "<", 1))
	{
		cmd->filein = cmd->command[i + 1];
		cmd->fdin = open(cmd->filein, O_RDONLY);
		if (cmd->fdin == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		cmd->command[i] = NULL;
	}
}

int	check_redir_aux(t_full_comm *cmd, int i)
{	
	if (!cmd->command[1] && !ft_strncmp(cmd->command[0], "<<", 2))
	{
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putendl_fd("near unexpected token `newline'", 2);
		g_exit_value = 256;
		return (1);
	}
	else
	{
		heredoc(cmd->command[i + 1]);
		/* if (cmd->command[i + 2])
			return (0);
		else */
		return (1);
	}	
}

int	check_redir(t_full_comm *cmd)
{
	int	i;

	i = 0;
	while (cmd->command[i])
	{
		if (!ft_strncmp(cmd->command[i], "<<", 2))
		{
			if (check_redir_aux(cmd, i) == 1)
				return (1);
			else
				return (0);
		}
		if (!ft_strncmp(cmd->command[i], ">>", 2))
			file_out(cmd, i);
		else if (!ft_strncmp(cmd->command[i], ">", 1))
			file_out(cmd, i);
		else if (!ft_strncmp(cmd->command[i], "<", 1))
			file_in(cmd, i);
		i++;
	}
	return (0);
}

void	redir_solo_cmd(t_full_comm *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
}
