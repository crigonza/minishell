/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:26:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/15 17:17:40 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void is_builtin(t_command **command, t_list **envp)
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
        env(envp, (*command)->command);
    else if(!ft_strncmp("/bin/export", com, ft_strlen(com)))
        insert_env(envp, (*command)->command);
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