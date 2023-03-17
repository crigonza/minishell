/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:35:20 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/15 17:12:48 by crigonza         ###   ########.fr       */
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

void    insert_env(t_list **envp, char **command)
{
    /* t_list  *temp;

    temp = *envp; */

    ft_lstadd_back(envp, ft_lstnew(command[1]));
}