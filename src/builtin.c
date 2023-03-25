/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:26:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/24 21:10:54 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int is_builtin(char *cmd)
{
    if(!ft_strncmp("/bin/echo", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("/bin/pwd", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("/bin/cd", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("/bin/env", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("/bin/export", cmd, ft_strlen(cmd)))
        return(1);
    else if(!ft_strncmp("/bin/unset", cmd, ft_strlen(cmd)))
        return(1);
    else
        return(0);
}

void builtin_exe(char **cmd, char **envp)
{
    char *com;
    int exit;

    com = cmd[0];
    if(!ft_strncmp("/bin/echo", com, ft_strlen(com)))
        echo(cmd);
    else if(!ft_strncmp("/bin/pwd", com, ft_strlen(com)))
        pwd(cmd);
    else if(!ft_strncmp("/bin/cd", com, ft_strlen(com)))
        cd(cmd);
    /* else if(!ft_strncmp("/bin/env", com, ft_strlen(com)))
        env(envp, comm->command);
    else if(!ft_strncmp("/bin/export", com, ft_strlen(com)))
        export(envp, comm->command); */
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

void env(t_list **envp, char **command)
{
    t_list *tmp;

    tmp = *envp;
    if(!command[1])
    {
        while(tmp != NULL)
        {
            ft_putendl_fd(tmp->content, 1);
            tmp = tmp->next;
        }
    }
    else
       ft_putendl_fd("env: too many arguments", 2); 
}

void    export(char **envp, char **command)
{
    char **tmp_ev;
    int equal;
    int i;

    i = 0;
    equal = 0;
    while(command[1][i])
    {
        if(command[1][i] == '=')
            equal = 1;
        i ++;
    }
    if(!equal)
    {
        write(1, "\n", 1);
        //return(NULL);
    }
    else
    {
        tmp_ev = malloc(sizeof(i) + 2);
        tmp_ev = envp;
        tmp_ev[i + 1] = command[1];
        tmp_ev[i + 2] = NULL;
    }
    i = 0;
    while (tmp_ev[i])
    {
        printf("%s\n", tmp_ev[i]);
        i++;
    }
    //return(tmp_ev);
}