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
				break ;
			add_history(prompt);
			init_lexer(prompt, envp, ev);
		}
		else
			break ;
	}
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