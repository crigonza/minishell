/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:52:11 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 23:32:44 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	order_vars(t_ev **envp)
{
	t_ev	*tmp;
	t_ev	*aux;
	int		change;

	change = 1;
	aux = NULL;
	while (change)
	{
		change = 0;
		tmp = *envp;
		while (tmp->next != aux)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				change_values(tmp, tmp->next);
				change = 1;
			}
			tmp = tmp->next;
		}
		aux = tmp;
	}
}

void	print_order_ev(t_ev **envp)
{
	t_ev	*tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

t_ev	*export_whout_args_aux(t_ev *tmp, t_ev *env, t_ev *ordered_env)
{
	t_ev	*head;

	head = NULL;
	while (env != NULL)
	{
		tmp = malloc(sizeof(t_ev));
		tmp->key = ft_strdup(env->key);
		tmp->value = ft_strdup(env->value);
		tmp->next = NULL;
		if (ordered_env == NULL)
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
	return (head);
}

void	export_whout_args(t_ev **envp)
{
	t_ev	*tmp;
	t_ev	*env;
	t_ev	*head;
	t_ev	*ordered_env;

	env = *envp;
	tmp = NULL;
	ordered_env = NULL;
	head = export_whout_args_aux(tmp, env, ordered_env);
	order_vars(&head);
	print_order_ev(&head);
	free_envp(&head);
}

void	export(t_ev **env, char *key, char *value)
{
	t_ev	*tmp;
	t_ev	*export;

	tmp = *env;
	export = new_ev(key, value);
	while (tmp->next != NULL && tmp->next->next != NULL)
	{
		tmp = tmp->next;
	}
	export->next = tmp->next;
	tmp->next = export;
}
