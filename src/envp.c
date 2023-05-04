/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:35:20 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/04 13:04:46 by itorres-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/minishell.h"

t_ev	*new_ev(char *key, char *value)
{
	t_ev	*new;

	new = malloc(sizeof(t_ev));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	add_ev(t_ev **env, t_ev *new)
{
	t_ev	*tmp;

	tmp = *env;
	if (*env == NULL)
		*env = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	ev_len(t_ev **env)
{
	int		i;
	t_ev	*tmp;

	i = 0;
	tmp = *env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	free_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free (env);
}

char	**convert_envp(t_ev **env)
{
	char	**envp;
	char	*aux;
	t_ev	*tmp;
	int		i;

	i = ev_len(env);
	tmp = *env;
	envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp != NULL)
	{
		aux = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin(aux, tmp->value);
		tmp = tmp->next;
		free(aux);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	set_envp(char **envp, t_ev **env)
{
	int		i;
	int		j;
	char	**vars;

	i = 0;
	while (envp[i])
	{
		vars = ft_split(envp[i], '=');
		add_ev(env, new_ev(vars[0], vars[1]));
		j = 0;
		while (vars[j])
		{
			free(vars[j]);
			j++;
		}
		free (vars);
		i++;
	}
}
