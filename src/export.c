/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:52:11 by crigonza          #+#    #+#             */
/*   Updated: 2023/04/24 20:57:04 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void order_vars(t_ev **envp)
{
    t_ev    *tmp;
    char    *aux;

    tmp = *envp;
    while(tmp->next != NULL)
    {
        if(ft_strncmp(tmp->key, tmp->next->key, 2) > 0)
        {
            aux = ft_strdup(tmp->key);
            free(tmp->key);
            tmp->key = ft_strdup(tmp->next->key);
            free(tmp->next->key);
            tmp->next->key = ft_strdup(aux);
            free(aux); 
        }
        tmp = tmp->next;
    }
}

void   print_order_ev(t_ev **envp)
{
    t_ev    *tmp;

    tmp = *envp;
    while(tmp != NULL)
    {
        printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void export_whout_args(t_ev **envp)
{
    t_ev    *tmp;
    t_ev    *env;
    t_ev    *head;
    t_ev    *ordered_env;

    env = *envp;
    tmp = NULL;
    ordered_env = NULL;
    while(env != NULL)
    {
        tmp = malloc(sizeof(t_ev));
        tmp->key = ft_strdup(env->key);
        tmp->value = ft_strdup(env->value);
        tmp->next = NULL;
        if(ordered_env == NULL)
        {
            ordered_env = tmp;
            head = ordered_env;
        }
        else
        {
            ordered_env->next = tmp;
            ordered_env = ordered_env->next;
        }
        env = env->next;
    }
    order_vars(&head);
    print_order_ev(&head);
    free_envp(&head);
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
    int     i;

    i = 0;
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
    else
        export_whout_args(envp);
}