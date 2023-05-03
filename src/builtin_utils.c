/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:21:49 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/03 19:45:21 by crigonza         ###   ########.fr       */
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

void builtin_exe(t_full_comm *cmd, t_ev **envp)
{
    char *com;
    pid_t pid;

    com = cmd->command[0];
    if(!ft_strncmp("export", com, ft_strlen(com)))
        export_builtin(envp, cmd->command);
    else if(!ft_strncmp("unset", com, ft_strlen(com)))
        unset_builtin(envp, cmd->command);
    else if(!ft_strncmp("cd", com, ft_strlen(com)))
            cd_builtin(envp, cmd->command);
    else
    {
        pid = fork();
        if (pid == 0)
        {
            redir_solo_cmd(cmd);
            if(!ft_strncmp("echo", com, ft_strlen(com)))
                echo_builtin(cmd->command);
            else if(!ft_strncmp("pwd", com, ft_strlen(com)))
                pwd_builtin(cmd->command);
            else if(!ft_strncmp("env", com, ft_strlen(com)))
                env_builtin(envp, cmd->command);
            exit(EXIT_SUCCESS);
        }
        else
            waitpid(pid, NULL, 0);
    }
}

void last_builtin_pipe(t_full_comm *cmd, t_ev **envp, int prpipe)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(prpipe, STDIN_FILENO);
		close(prpipe);
		builtin_exe(cmd, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close (prpipe);
		waitpid(-1, NULL, 0);
	}
}

void builtin_pipe(t_full_comm *cmd, t_ev **envp, int *prpipe)
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

int check_key(t_ev **env, char *key, char *value)
{
    t_ev    *tmp;

    tmp = *env;
    while (tmp != NULL)
    {
        if(!ft_strncmp(key, tmp->key, ft_strlen(key)))
        {
            free(tmp->value);
            tmp->value = value;
            return(1);
        }
        tmp = tmp->next;
    }
    return(0);
}
