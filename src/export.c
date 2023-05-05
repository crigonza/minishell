/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:52:11 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/05 13:54:28 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	order_vars(t_ev **envp)
{
	t_ev	*tmp;
	char	*aux;

	tmp = *envp;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->key, tmp->next->key, 2) > 0)
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

void	export_whout_args_aux(t_ev	*tmp, t_ev	*env, t_ev	*head, \
								t_ev	*ordered_env)
{
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
	head = NULL;
	export_whout_args_aux(tmp, env, head, ordered_env);
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
