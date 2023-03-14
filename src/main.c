#include "../inc/minishell.h"

void	init_prompt(char **envp)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("\e[34m"
							"MiniShell$>"
							"\x1b[m");
		if (ft_strlen(prompt) > 0)
		{
			if (strncmp(prompt, "exit", ft_strlen(prompt)) == 0)
				break ;
			add_history(prompt);
			init_lexer(prompt, envp);
		}
		else
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*envp_lst;
	t_list	*tmp;

	envp_lst = malloc(sizeof(t_list));
	envp_lst = NULL;
	list_envp(envp, &envp_lst);
    //printf("%s", envp_lst->content);
	/* tmp = *envp_lst;
	while(tmp->next == NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	} */
	//init_prompt(envp_lst);
	system("leaks -q minishell");
	return (0);
}