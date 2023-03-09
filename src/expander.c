/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/09 11:54:52 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
char	*get_envp_2(char *content, char *expanded)
{
	char	*tmp;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (content[i] != '$')
		i++;
	i++;
	while ((content[i] >= 'A' && content[i] <= 'Z') || content[i] == '(' || content[i] == ')')
		i++;
	if (!content[i])
		return (expanded);
	else
		{
			while(content[i])
			{
				i++;
				j++;
			}
			tmp = malloc(sizeof(j + 1));
			ft_strlcpy(tmp, &content[i - j], j + 1);
			expanded = ft_strjoin(expanded, tmp);
			return(expanded);
		}
}
char	*get_envp(char *content, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*expanded;

	i = 0;
	key = get_envp_key(content);
	value = get_envp_value(envp, key);
    if (content[i] != '$')
    {
        while(content[i] != '$')
            i++;
        expanded = malloc(sizeof(i) + 1);
        ft_strlcpy(expanded, content, i + 1);
        expanded = ft_strjoin(expanded, value);
    }
    else
        expanded = value;
	expanded = get_envp_2(content, expanded);
	//printf("%s----%d\n", expanded, i);
	return (expanded);
}

char	*get_envp_key(char *content)
{
	char	*envp_key;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (content[i] != '$')
		i++;
	if (content[i + 1] == '(')
		i += 2;
	else
		i++;
	while (content[i] >= 'A' && content[i] <= 'Z')
	{
		i++;
		j++;
	}
	envp_key = malloc(sizeof(j + 1));
	ft_strlcpy(envp_key, &content[i - j], j + 1);
	return (envp_key);
}

char	*get_envp_value(char **envp, char *search)
{
	int		i;
	char	*value;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], search, ft_strlen(search)))
			break ;
		i++;
	}
	/* while (envp[i][j] != '=')
		j++; */
	tmp = ft_strchr(envp[i], '=') + 1;
	value = malloc(sizeof(ft_strlen(tmp) + 1));
    ft_strlcpy(value, tmp, ft_strlen(tmp) + 1);
	//printf("%s\n", value);
	return (value);
}

void	expander(t_lexer **lexer)
{
	t_lexer	*tmp;
	char	**envp;
	int		i;

	tmp = *lexer;
	envp = (*lexer)->envp;
	while (tmp != NULL)
	{
        if (tmp->token_type != PIPE)
		{
            i = 0;
			while (tmp->content[i] != '\0')
			{
				if (tmp->content[i] == '$')
				{
					tmp->content = get_envp(tmp->content, envp);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	free(tmp);
	print_lexer(lexer);
	parser(lexer);
}

void	retokenize(t_lexer **lexer)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = *lexer;
	while (tmp != NULL)
	{
		if (tmp->token_type == COMMAND)
		{
			if (!ft_strncmp(tmp->content, "echo\0", 5))
				tmp->next->token_type = STRING;
			while (tmp->content[i])
			{
				if (tmp->content[i] == '/')
					tmp->token_type = PATH;
				i++;
			}
		}
		tmp = tmp->next;
	}
	free(tmp);
	expander(lexer);
}
