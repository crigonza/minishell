/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:35:20 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/14 13:20:33 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void    export(char **envp, char **command)
{
    
} */

void  list_envp(char **envp, t_list **envp_lst)
{
    int i;

    i = 0;
    while(envp[i])
    {
        ft_lstadd_back(envp_lst, ft_lstnew(envp[i]));
        i++;
    }
}
char    **insert_env(char **envp, char **command)
{
    int i;
    int len;
    char **temp;

    i = 0;
    len = 0;
    while(envp[len])
        len++;
    temp = malloc(sizeof(char*) * len + 1);
    while(envp[i])
    {
        temp[i] = malloc(sizeof(ft_strlen(envp[i])));
        ft_strlcpy(temp[i], envp[i], ft_strlen(envp[i]));
        i++;
    }
    temp[i] = malloc(sizeof(ft_strlen(command[1])));
    ft_strlcpy(temp[i], command[1], ft_strlen(command[1]));
    i = 0;
    while(temp[i])
    {
        printf("%s\n", temp[i]);
        i++;
    }
    /* i++;
    temp[i] = malloc(sizeof(ft_strlen(envp[len])));
    ft_strlcpy(temp[i], envp[len], ft_strlen(envp[len])); */
    //free(envp);
    return(temp);
}