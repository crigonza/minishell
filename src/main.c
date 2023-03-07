#include "../inc/minishell.h"

void	init_prompt(void)
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
			init_lexer(prompt);
		}
		else
			break ;
	}
}

int	main(int argc, char **argv, char **ev)
{
	init_prompt();
	system("leaks -q minishell");
	return (0);
}