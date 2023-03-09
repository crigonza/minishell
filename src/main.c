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
    int i;

    i = 0;
    get_envp_value(envp, "PWD");
    /* while(envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    } */
    
	init_prompt(envp);
	system("leaks -q minishell");
	return (0);
}