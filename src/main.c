#include "../inc/minishell.h"

void	init_prompt(t_list **envp, char **ev)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("\e[34m"
							"MiniShell$>"
							"\x1b[m");
		if (ft_strlen(prompt) > 0)
		{
			if (strncmp(prompt, "exit", 4) == 0)
				exit_v(prompt);
			add_history(prompt);
			init_lexer(prompt, envp, ev);
		}
		else
			break;
	}
}

void exit_v(char *prompt)
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
	exit(exit_val);
}

void	free_envp(t_list **envp)
{
	t_list	*tmp;

	while ((*envp) != NULL)
	{
		tmp = (*envp);
		(*envp) = (*envp)->next;
		free(tmp);
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_list	*envp_lst;

	(void)argc;
	(void)argv;
	envp_lst = malloc(sizeof(t_list));
	envp_lst = NULL;
	list_envp(envp, &envp_lst);
	init_prompt(&envp_lst, envp);
	free_envp(&envp_lst);
	system("leaks -q minishell");
	return (0);
}