/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:49:07 by crigonza          #+#    #+#             */
/*   Updated: 2023/04/17 18:01:08 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	file_out(t_full_comm *cmd)
{
	int i;

	i = 0; 
	while(cmd->command[i])
	{
		if(!ft_strncmp(cmd->command[i], ">>", 2) || !ft_strncmp(cmd->command[i], ">", 1))
		{
			cmd->fileout = cmd->command[i + 1];
			if(!ft_strncmp(cmd->command[i], ">>", 2))
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
		i++;
	}
}

void    file_in(t_full_comm *cmd)
{
    int i;

    i =  0;
    while(cmd->command[i])
    {
        if(!ft_strncmp(cmd->command[i], "<", 1))
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
        i ++;
    }
}

int	check_redir(t_full_comm *cmd)
{
    int i;

	i = 0;
    while (cmd->command[i]) 
	{
		if(!ft_strncmp(cmd->command[i], ">>", 2))
			file_out(cmd);
        else if (!ft_strncmp(cmd->command[i], ">", 1))
			file_out(cmd);
		else if(!ft_strncmp(cmd->command[i], "<<", 2))
		{
			heredoc(cmd->command[i + 1]);
            if(!cmd->command[i + 2])
			    return (1);
		}
		else if(!ft_strncmp(cmd->command[i], "<", 1))
            file_in(cmd);
        i++;
    }
	return(0);
}

void redir_solo_cmd(t_full_comm *cmd)
{
	if(cmd->fdin != STDIN_FILENO)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if(cmd->fdout != STDOUT_FILENO)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
}