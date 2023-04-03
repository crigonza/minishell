/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:11:13 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/28 11:45:31 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_prompt(t_ev **env)
{
	char	*prompt;
	int		exit_val;

	exit_val = 0;
	while (1)
	{
		config_signals();
		prompt = readline("\e[34m""MiniShell$>""\x1b[m");
		 if (!prompt)
        {
            printf("exit\n");  // CTRL + D
            exit(-1);
        }
		if (ft_strlen(prompt) > 0)
		{
			if (strncmp(prompt, "exit", 4) == 0)
			{
				exit_val = exit_v(prompt);
				break;
			}
			add_history(prompt);
			init_lexer(prompt, env);
		}	  
	}
	
	return(exit_val);
}

int exit_v(char *prompt)
{
	char *exit_arg;
	int exit_val;
	int i;

	i = 0;
	exit_val = 0;
	exit_arg = ft_substr(prompt, 5, ft_strlen(prompt) - 4);
	if (exit_arg[i] == '-')
		i++;
	while(exit_arg[i] && ft_isalnum(exit_arg[i]))
		i++;
	if (exit_arg[i] == '\0')
		exit_val = ft_atoi(exit_arg);
	if (exit_val < 0)
	{
		exit_val *= -1;
		exit_val = exit_val % 256;
		exit_val = 256 - exit_val;
	}
	else
		exit_val = exit_val % 256;
	free(exit_arg);
	return(exit_val);
}

void	free_envp(t_ev **env)
{
	t_ev	*tmp;

	while ((*env) != NULL)
	{
		tmp = (*env);
		(*env) = (*env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ev	*env;
	int		exval;

	(void)argc;
	(void)argv;
	env = malloc(sizeof(t_ev));
	env = NULL;
	set_envp(envp, &env);
	exval = init_prompt(&env);
	free_envp(&env);
	free(env);
	rl_clear_history();
	system("leaks -q minishell");
	exit (exval);
}
