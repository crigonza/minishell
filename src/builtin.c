/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:26:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/04/12 19:48:41 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void echo_builtin(char **command)
{
    if (!ft_strncmp(command[1], "-n", 2))
        ft_putstr_fd(command[2], 1);
    else
        ft_putendl_fd(command[1], 1);
}

void pwd_builtin(char **command)
{
    if(!command[1])
        ft_putendl_fd(getcwd(NULL, 0), 1);
    else
        ft_putendl_fd("pwd: too many arguments", 2);
}

void cd_builtin(char **command)
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

void env_builtin(t_ev **envp, char **command)
{
    t_ev *tmp;

    tmp = *envp;
    if(!command[1])
    {
        while(tmp != NULL)
        {
            printf("%s=%s\n", tmp->key, tmp->value);
            tmp = tmp->next;
        }
    }
    else
       ft_putendl_fd("env: too many arguments", 2); 
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

void export(t_ev **env, char *key, char *value)
{
    t_ev    *tmp;
    t_ev    *export;

    tmp = *env;
    export = new_ev(key, value);
    while(tmp->next != NULL && tmp->next->next != NULL)
    {
        tmp = tmp->next;
    }
    export->next = tmp->next;
    tmp->next = export;
}

void    export_builtin(t_ev **envp, char **command)
{
    char    *key;
    char    *value;
    t_ev    *tmp;
    int     i;

    i = 0;
    tmp = *envp;
    if (command[1])
    {
        while(command[1][i] != '=')
            i++;
        if(command[1][i] == '=' && i != 0)
        {
            value = ft_strdup(&command[1][i + 1]);
            key = malloc(sizeof(char) * i + 1);
            ft_strlcpy(key, command[1], i + 1);
            if (!check_key(envp, key, value))
                export(envp, key, value);
        }
    }
}

void unset_builtin(t_ev **envp, char **command)
{
    t_ev    *tmp;
    t_ev    *prev;

    tmp = *envp;
    while(tmp != NULL)
    {
        if(!ft_strncmp(tmp->key, command[1], ft_strlen(command[1])))
            break;
        prev = tmp;
        tmp = tmp->next;
    }
    if(tmp != NULL)
    {
        prev->next = tmp->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}