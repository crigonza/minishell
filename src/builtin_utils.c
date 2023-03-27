/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:21:49 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/27 21:00:00 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int is_builtin(char *cmd)
{
    if(!ft_strncmp("echo", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("cd", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("env", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("export", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("unset", cmd, ft_strlen(cmd)))
        return(1);
    else
        return(0);
}

void builtin_exe(char **cmd, t_ev **envp)
{
    char *com;
    int exit;

    com = cmd[0];
    if(!ft_strncmp("echo", com, ft_strlen(com)))
        echo_builtin(cmd);
    else if(!ft_strncmp("pwd", com, ft_strlen(com)))
        pwd_builtin(cmd);
    else if(!ft_strncmp("cd", com, ft_strlen(com)))
        cd_builtin(cmd);
    else if(!ft_strncmp("env", com, ft_strlen(com)))
        env_builtin(envp, cmd);
    else if(!ft_strncmp("export", com, ft_strlen(com)))
        export_builtin(envp, cmd);
    else if(!ft_strncmp("unset", com, ft_strlen(com)))
        unset_builtin(envp, cmd);
}

void builtin_pipe(char **cmd, t_ev **envp, int *prpipe)
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
		builtin_exe(cmd, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		close (*prpipe);
		*prpipe = fd[0];
		waitpid(-1, NULL, 0);
	}
}
