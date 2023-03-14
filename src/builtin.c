/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:26:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/14 12:37:05 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void is_builtin(t_command **command)
{
    char *com;
    /* char **env_tmp;

    env_tmp = (*command)->envp; */
    com = (*command)->command[0];
    if(!ft_strncmp("/bin/echo", com, ft_strlen(com)))
        echo((*command)->command);
    else if(!ft_strncmp("/bin/pwd", com, ft_strlen(com)))
        pwd((*command)->command);
    else if(!ft_strncmp("/bin/cd", com, ft_strlen(com)))
        cd((*command)->command);
    else if(!ft_strncmp("/bin/env", com, ft_strlen(com)))
        env((*command)->envp, (*command)->command);
    else if(!ft_strncmp("/bin/export", com, ft_strlen(com)))
    {
        //free((*command)->envp);
        (*command)->envp = insert_env((*command)->envp, (*command)->command);
    }
    else
        executer((*command)->command, (*command)->envp);

}

void echo(char **command)
{
    if (!ft_strncmp(command[1], "-n", 2))
        ft_putstr_fd(command[2], 1);
    else
        ft_putendl_fd(command[1], 1);
}

void pwd(char **command)
{
    if(!command[1])
        ft_putendl_fd(getcwd(NULL, 0), 1);
    else
        ft_putendl_fd("pwd: too many arguments", 2);
}

void cd(char **command)
{
    int val;

    if(!command[2])
    {
        val = chdir(command[1]);
        if (val == -1)
        {
            ft_putstr_fd("cd: no such file or directory: ", 2);
            ft_putendl_fd(command[1], 2);
        }
    }
    else
    {
        ft_putstr_fd("cd: string not in pwd: ", 2);
        ft_putendl_fd(command[1], 2);
    }
}

void env(char **envp, char **command)
{
    int i;

    i = 0;
    if(!command[1])
    {
        while(envp[i])
        {
            printf("%s\n", envp[i]);
            i++;
        }
    }
    else
       ft_putendl_fd("env: too many arguments", 2); 
}